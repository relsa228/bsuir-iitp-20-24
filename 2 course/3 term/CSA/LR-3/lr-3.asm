.model small
.stack 256

data segment
a   dw   0
b   dw   0
c   dw   0
d   dw   0
max   dw   0
error   dw   0
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
maxlenA db 30
actlenA db ?
fldA db 30 dup('$')

parB label byte
maxlenB db 30
actlenB db ?
fldB db 30 dup('$')

parC label byte
maxlenC db 30
actlenC db ?
fldC db 30 dup('$')

parD label byte
maxlenD db 30
actlenD db ?
fldD db 30 dup('$')

data ends

code segment
assume cs:code, ds:data

outInt2 proc near
test    ax, ax
   jns  @OutNeg
   mov  cx, ax
   mov     ah, 02h
   mov     dl, '-'
   int     21h
   mov  ax, cx
   neg     ax
@OutNeg:  
    xor     cx, cx
    mov     bx, 10
@OutLoopFirst:
    xor     dx,dx
    div     bx
    push    dx
    inc     cx
    test    ax, ax
    jnz     @OutLoopFirst
    mov     ah, 02h
@OutLoopSec:
    pop     dx
    add     dl, '0'
    int     21h
    loop    @OutLoopSec
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
    mov cx, [bx]                                       
    xor ch, ch
    mov si, 1                                           

    @loopMet:

    push si                                            
    mov si, cx                                         
    cmp cx,1
    je @Signed
    @NoSigned:
    mov ax, [bx+si]
    xor ah, ah   

    cmp al, 30h
    jb @Error
    cmp al, 39h
    ja @Error

    pop si                                             
    sub ax, 30h                                        
    mul si        
    jo @Overflow                       
    add di, ax                                
    mov ax, si                                         
    mov dx, 10
    mul dx                                          
    mov si, ax                       
    loop @loopMet                                      
    
    @return:
    call makeIntend
    ret

    @Signed:
    push dx
    mov dx,[bx+si]
    xor dh,dh
    cmp dl,'-'
    pop dx
    jne @NoSigned
    neg di
    pop si
    jmp @return

    @Error:
    mov error, 1
    pop cx
    jmp @return

    @Overflow:
    mov error, 1
    jmp @return
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
        
        @errorInputA: 
        mov error, 0                                 
        lea dx, errorMessage
        mov ah, 09
        int 21h
        call makeIntend
        @firstTryA:
        lea dx, enterA                                     
        mov ah, 09
        int 21h
        lea dx, parA
        mov ah, 0Ah
        int 21h
        lea bx, parA+1                                  
        call enterNum
        mov a, di
        cmp error, 1
        je @errorInputA
        jmp @firstTryB

        @errorInputB: 
        mov error, 0                                    
        lea dx, errorMessage
        mov ah, 09
        int 21h
        call makeIntend
        @firstTryB:
        lea dx, enterB                                    
        mov ah, 09
        int 21h
        lea dx, parB
        mov ah, 0Ah
        int 21h
        lea bx, parB+1                                  
        call enterNum
        mov b, di
        cmp error, 1
        je @errorInputB
        mov ax, b
        cmp ax, 0
        je @errorInputB
        mov ax, a
        mul ax
        mov bx, b
        cmp ax, bx
        je @errorInputB
        jmp @firstTryC

        @errorInputC:
        mov error, 0                                     
        lea dx, errorMessage
        mov ah, 09
        int 21h
        call makeIntend
        @firstTryC:
        lea dx, enterC                                   
        mov ah, 09
        int 21h
        lea dx, parC
        mov ah, 0Ah
        int 21h
        lea bx, parC+1                                  
        call enterNum
        mov c, di
        cmp error, 1
        je @errorInputC
        jmp @firstTryD

        @errorInputD: 
        mov error, 0                                   
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
        cmp error, 1
        je @errorInputD

        mov ax, a
        imul a
        jc @overflowPow2a              
        jnc @notOverflowPow2a   

        @overflowPow2a:                                 
        lea dx, overflowReportPow2a
        call overflow

        @notOverflowPow2a:                  
        imul a
        jo @overflowPow3a    
        jno @notOverflowPow3a  

        @overflowPow3a:                                 
        lea dx, overflowReportPow3a
        call overflow

        @notOverflowPow3a:                             
        imul a           
        jo @overflowPow4a 
        jno @notOverflowPow4a

        @overflowPow4a:                                 
        lea dx, overflowReportPow4a
        call overflow                                 

        @notOverflowPow4a:
        mov bx, b
        cmp ax, bx                                      
        jg @biggerFirstCMP
        jle @midP

        @biggerFirstCMP:                                
            mov ax, c
            imul b
            jo @overflowMulCB 
            jno @notOverflowMulCB 

            @OverflowMulCB:                             
            lea dx, overflowReportMulCB
            call overflow 

            @notOverflowMulCB:     
            mov bx, ax
            mov ax, d
            xor dx, dx
            idiv b
            
            jo @overflowDivDB
            jno @notOverflowDivDB
            
            @overflowDivDB:                             
            lea dx, overflowReportDivDB
            call overflow
            
            @notOverflowDivDB:                            
            cmp ax, bx                                  
            je @equalSecondCMP
            jne @notEqualSecondCMPStart

                @equalSecondCMP:                        
                    mov ax, a
                    mov bx, b
                    or ax, bx
                    mov result, ax
                    jmp @exit                           

                @notEqualSecondCMPStart:                
                    mov ax, a
                    mov bx, b
                    cmp ax, bx            
                    jge @biggerOrEqualMaxF
                    jl @smallerMaxF

                    @midP:
                        jmp @notBiggerFirstCMP
                    .findMax:                           

                    @biggerOrEqualMaxF:                 
                        mov bx, c
                        cmp ax, bx
                        jge @biggerOrEqualMaxS
                        jl @smallerMaxS

                    @biggerOrEqualMaxS:                 
                        mov max, ax
                        jmp @notEqualSecondCMPEnd

                    @smallerMaxS:                       
                        mov max, bx
                        jmp @notEqualSecondCMPEnd

                    @smallerMaxF:                      
                        mov ax, c
                        cmp bx, ax
                        jge @biggerOrEqualMaxT
                        jl @smallerMaxT

                    @biggerOrEqualMaxT:                
                        mov max, bx
                        jmp @notEqualSecondCMPEnd

                    @smallerMaxT:                      
                        mov max, ax
                        jmp @notEqualSecondCMPEnd

                    .findMaxEnd:


                @notEqualSecondCMPEnd:                  
                    mov ax, a
                    imul a                                 
                    sub ax, b
                    jc @overflowSubAB
                    jno @notOverflowSubAB
                    
                    @OverflowSubAB:
                    lea dx, overflowReportSub
                    call overflow
                    
                    @notOverflowSubAB:               
                    mov bx, ax
                    mov ax, max
                    xor dx, dx
                    idiv bx
                    jo @overflowDiv1
                    jno @notOverflowDiv1
                    
                    @overflowDiv1:
                    lea dx, overflowReportDiv1
                    call overflow
                    
                    @notOverflowDiv1:
                    mov result, ax
                    jmp @exit                          

        @notBiggerFirstCMP:                            
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
            mov result, ax                                 

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