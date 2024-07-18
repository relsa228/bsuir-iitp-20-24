.model small
.stack 256

data segment
a   dw   0
b   dw   0
c   dw   0
d   dw   0
max   dw   0
result   dw   0

enterA db 'Enter a: $'
enterB db 'Enter b: $'
enterC db 'Enter c: $'
enterDD db 'Enter d: $'
outResult db 'Result: $'
errorMessage db 'Input error! Try again.$'
overflowReportPow2a db 'Overflow in a^2$'
overflowReportPow3a db 'Overflow in a^3$'
overflowReportPow4a db 'Overflow in a^4$'
overflowReportMulCB db 'Overflow in c*b$'
overflowReportDivDB db 'Overflow in d/b$'
overflowReportSub db 'Overflow in pow(a,2)-b$'
overflowReportDiv1 db 'Overflow in max(a,b,c)/(pow(a,2)-b)$'
overflowReportPowC2 db 'Overflow in c^2$'
overflowReportPowC3 db 'Overflow in c^3$'
overflowReportAdd db 'Overflow in c^3 + b$'
indent  db '', 0Dh, 0Ah, '$'

parA label byte
maxlenA db 10
actlenA db ?
fldA db 10 dup('$')

parB label byte
maxlenB db 10
actlenB db ?
fldB db 10 dup('$')

parC label byte
maxlenC db 10
actlenC db ?
fldC db 10 dup('$')

parD label byte
maxlenD db 10
actlenD db ?
fldD db 10 dup('$')

data ends

code segment
assume cs:code, ds:data

outInt2 proc near
test    ax, ax
   jns     oi1
   mov  cx, ax
   mov     ah, 02h
   mov     dl, '-'
   int     21h
   mov  ax, cx
   neg     ax
oi1:  
    xor     cx, cx
    mov     bx, 10
oi2:
    xor     dx,dx
    div     bx
    push    dx
    inc     cx
    test    ax, ax
    jnz     oi2
    mov     ah, 02h
oi3:
    pop     dx
    add     dl, '0'
    int     21h
    loop    oi3
    ret
outInt2 endp

makeIntend proc near
    lea dx, indent
    mov ah, 09
    int 21h
    ret
makeIntend endp

enterNum proc near
    mov di, 0           
    mov cx, [bx]                                       ;в CX количество введенных символов
    xor ch, ch
    mov si, 1                                          ;в SI множитель 
    @loopMet:
    push si                                            ;сохраняем SI (множитель) в стеке
    mov si, cx                                         ;в SI помещаем номер текущего символа 
    mov ax, [bx+si]                                    ;в AX помещаем текущий символ 
    xor ah, ah
    pop si                                             ;извлекаем множитель (SI) из стека
    sub ax, 30h                                        ;получаем из символа (AX) цифру
    mul si                                             ;умножаем цифру (AX) на множитель (SI)
    add di, ax                                         ;складываем с результирующим числом
    mov ax, si                                         ;помещаем множитель (SI) в AX
    mov dx, 10
    mul dx                                             ;увеличиваем множитель (AX) в 10 раз
    mov si, ax                                         ;перемещаем множитель (AX) назад в SI
    loop @loopMet                                      ;переходим к предыдущему символу
    call makeIntend
    ret
enterNum endp

overflow proc near
    mov ah, 09
    int 21h
    mov ah, 4ch
    int   21h
overflow endp

start:
        mov ax, data
        mov ds, ax
        jmp @firstTryA
        
        @errorInputA:                                    ;Обработка исключения
        lea dx, errorMessage
        mov ah, 09
        int 21h
        call makeIntend
        @firstTryA:
        lea dx, enterA                                  ;вводим а   
        mov ah, 09
        int 21h
        lea dx, parA
        mov ah, 0Ah
        int 21h
        lea bx, parA+1                                  ;в BX адрес второго элемента буфера
        call enterNum
        mov a, di
        jo @errorInputA
        jmp @firstTryB

        @errorInputB:                                    ;Обработка исключения
        lea dx, errorMessage
        mov ah, 09
        int 21h
        call makeIntend
        @firstTryB:
        lea dx, enterB                                  ;вводим b   
        mov ah, 09
        int 21h
        lea dx, parB
        mov ah, 0Ah
        int 21h
        lea bx, parB+1                                  
        call enterNum
        mov b, di
        jo @errorInputB
        mov ax, b
        cmp ax, 0
        je @errorInputB
        mov ax, a
        mul ax
        mov bx, b
        cmp ax, bx
        je @errorInputB
        jmp @firstTryC

        @errorInputC:                                    ;Обработка исключения
        lea dx, errorMessage
        mov ah, 09
        int 21h
        call makeIntend
        @firstTryC:
        lea dx, enterC                                  ;вводим c   
        mov ah, 09
        int 21h
        lea dx, parC
        mov ah, 0Ah
        int 21h
        lea bx, parC+1                                  
        call enterNum
        mov c, di
        jo @errorInputC
        jmp @firstTryD

        @errorInputD:                                    ;Обработка исключения
        lea dx, errorMessage
        mov ah, 09
        int 21h
        call makeIntend
        @firstTryD:
        lea dx, enterDD   
        mov ah, 09                                 
        int 21h
        lea dx, parD
        mov ah, 0Ah
        int 21h
        lea bx, parD+1  
        call enterNum
        mov d, di
        jo @errorInputD

        mov ax, a
        imul a
        jo @overflowPow2a              
        jno @notOverflowPow2a   

        @overflowPow2a:                                 ;Overflow in a^2
        lea dx, overflowReportPow2a
        call overflow

        @notOverflowPow2a:                  
        imul a
        jo @overflowPow3a    
        jno @notOverflowPow3a  

        @overflowPow3a:                                 ;Overflow in a^3
        lea dx, overflowReportPow3a
        call overflow

        @notOverflowPow3a:                             
        imul a           
        jo @overflowPow4a 
        jno @notOverflowPow4a

        @overflowPow4a:                                 ;Overflow in a^4
        lea dx, overflowReportPow4a
        call overflow                                 

        @notOverflowPow4a:
        mov bx, b
        cmp ax, bx                                      ; первое сравнение (pow(a,4)>b)
        jg @biggerFirstCMP
        jle @midP

        @biggerFirstCMP:                                ; первая ветка первого сравнения  (pow(a,4)>b)
            mov ax, c
            imul b
            jo @overflowMulCB 
            jno @notOverflowMulCB 

            @OverflowMulCB:                             ;Overflow in c*b
            lea dx, overflowReportMulCB
            call overflow 

            @notOverflowMulCB:                            
            mov bx, ax
            mov ax, d
            idiv b
            jo @overflowDivDB
            jno @notOverflowDivDB
            
            @overflowDivDB:                             ;Overflow in d/b (lol)
            lea dx, overflowReportDivDB
            call overflow
            
            @notOverflowDivDB:                            
            cmp ax, bx                                  ; второе сравнение (c*b==d/b)
            je @equalSecondCMP
            jle @midP

                @equalSecondCMP:                        ; первая ветка второго сравнения (c*b==d/b)
                    mov ax, a
                    mov bx, b
                    or ax, bx
                    mov result, ax
                    jmp @exit                           ; result = a OR b

                @notEqualSecondCMPStart:                ; начало второй ветки второго сравнения (c*b!=d/b)
                    mov ax, a
                    mov bx, b
                    cmp ax, bx            
                    jge @biggerOrEqualMaxF
                    jl @smallerMaxF

                    @midP:
                        jmp @notBiggerFirstCMP
                    .findMax:                           ; поиск максисмального (сравнение а и b)

                    @biggerOrEqualMaxF:                 ; если а >= b - первая ветка
                        mov bx, c
                        cmp ax, bx
                        jge @biggerOrEqualMaxS
                        jl @smallerMaxS

                    @biggerOrEqualMaxS:                 ; если а >= c    => max = a (первая ветка)
                        mov max, ax
                        jmp @notEqualSecondCMPEnd

                    @smallerMaxS:                       ; если а < c    => max = c (первая ветка)
                        mov max, bx
                        jmp @notEqualSecondCMPEnd

                    @smallerMaxF:                       ; если а <= b - вторая ветка
                        mov ax, c
                        cmp bx, ax
                        jge @biggerOrEqualMaxT
                        jl @smallerMaxT

                    @biggerOrEqualMaxT:                 ; если b >= c    => max = b (первая вторая)
                        mov max, bx
                        jmp @notEqualSecondCMPEnd

                    @smallerMaxT:                       ; если b < c    => max = c (первая вторая)
                        mov max, ax
                        jmp @notEqualSecondCMPEnd

                    .findMaxEnd:


                @notEqualSecondCMPEnd:                  ; конец второй ветки второго сравнения (c*b!=d/b)
                    mov ax, a
                    imul a                                 
                    sub ax, b
                    jo @overflowSubAB
                    jno @notOverflowSubAB
                    
                    @OverflowSubAB:
                    lea dx, overflowReportSub
                    call overflow
                    
                    @notOverflowSubAB:               
                    mov bx, ax
                    mov ax, max
                    idiv bx
                    jo @overflowDiv1
                    jno @notOverflowDiv1
                    
                    @overflowDiv1:
                    lea dx, overflowReportDiv1
                    call overflow
                    
                    @notOverflowDiv1:
                    mov result, ax
                    jmp @exit                          ; result = max(a,b,c)/(pow(a,2)-b)

        @notBiggerFirstCMP:                            ; вторая ветка первого сравнения (pow(a,4)<=b)
            mov ax, c
            imul c
            jo @overflowPow2C
            jno @notOverflowPow2C

            @overflowPow2C:
            lea dx, overflowReportPowC2
            call overflow

            @notOverflowPow2C:                       
            imul c
            jo @overflowPow3C     
            jno @notOverflowPow3C

            @overflowPow3C:
            lea dx, overflowReportPowC3
            call overflow
                            
            @notOverflowPow3C:                             
            mov bx, b
            add ax, bx
            jo @overflowAdd
            jno @notOverflowAdd

            @overflowAdd:
            lea dx, overflowReportAdd
            call overflow
            
            @notOverflowAdd:                                   
            mov result, ax                                 ; result = pow(c,3) + b

    @exit:
        lea dx, outResult                                  
        mov ah, 09
        int 21h
        mov ax, result
        call outInt2
        mov ah, 4ch
        int   21h
code ends
    end start