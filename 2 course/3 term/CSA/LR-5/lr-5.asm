.model small
.stack 256

data segment

masF dw 10000 dup(0)
masS dw 10000 dup(0)
masFSize dw 0
masSSize dw 0
masResSize dw 0
result dw 0
buffCX dw 0
buffBX dw 0
buffDIF dw 0
buffBXS dw 0
str dw 0
strCount dw 0
col dw 0
colCount dw 0
enterCol db 'Enter the number of columns: $'
enterStr db 'Enter the number of lines: $'
fillMasF db 'Fill first array: $'
fillMasS db 'Fill second array: $'
resultStr db 'Result matrix: $'
symbolStr db 'Symbol $'
tireStr db ' - $'
error db 'Input error!$'
overflow db 'Overflow!$'
indent  db '', 0Dh, 0Ah, '$'
space db ':$'
spaceS db ' $'

parNum label byte
maxlenNum db 10
actlenNum db ?
fldNum db 10 dup('$')

parCol label byte
maxlenCol db 10
actlenCol db ?
fldCol db 10 dup('$')

parStr label byte
maxlenStr db 10
actlenStr db ?
fldStr db 10 dup('$')

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

fillArray proc near ;заполнение массива
    mov buffBX, 0
    mov buffCX, 0
    jmp @fillLoop
@makeCol:
    mov colCount, 0
    inc strCount
@fillLoop:
    mov buffBX, bx
    mov buffCX, cx
    mov ax, colCount
    cmp ax, col
    je @makeCol
    lea dx, symbolStr
    mov ah, 09
    int 21h
    mov ax, colCount
    call outInt2
    lea dx, space
    mov ah, 09
    int 21h
    mov ax, strCount
    call outInt2
    lea dx, tireStr
    mov ah, 09
    int 21h

    lea dx, parNum
    mov ah, 0Ah
    int 21h
    lea bx, parNum+1                                 
    call enterNum
    mov bx, buffBX
    mov [bx], di    ;Переслать DI в элемент массива
    add bx, 2     ;Разместить в BX адрес следующего элемента массива
    inc colCount
    call makeIntend
    mov cx, buffCX
loop @fillLoop

mov strCount, 0
mov colCount, 0
ret
fillArray endp

taskProc proc near
mov colCount, 0

lea di, masF
mov buffDIF, di

lea bx, masS
mov buffBXS, bx

jmp @taskLoop
@taskIntend:
    call makeIntend
    mov colCount, 0
    inc strCount
    jmp @proceed
@taskLoop:
    mov bx, buffBXS
    mov ax, [bx]
    mov di, buffDIF
    mov dx, [di]
    imul dx
    jc @overflowLoop
    mov result, ax

    mov ax, colCount
    cmp ax, col
    je @taskIntend

    @proceed:

    mov ax, result
    mov buffCX, cx
    call outInt2
    mov cx, buffCX
    lea dx, spaceS
    mov ah, 09
    int 21h

    mov di, buffDIF
    add di, 2
    mov buffDIF, di

    mov bx, buffBXS
    add bx, 2
    mov buffBXS, bx

    inc colCount

loop @taskLoop

@end:
ret

@overflowLoop:
    lea dx, overflow
    mov ah, 09
    int 21h
    jmp @end
    
taskProc endp

makeIntend proc near
    lea dx, indent
    mov ah, 09
    int 21h
    ret
makeIntend endp

start:
    mov ax, data
    mov ds, ax
    jmp @firstTryStr

@errorInputStr:     ;ввод размерности массива
    lea dx, error
    mov ah, 09
    int 21h
    call makeIntend
@firstTryStr:
    lea dx, enterStr
    mov ah, 09
    int 21h
    lea dx, parStr
    mov ah, 0Ah
    int 21h
    lea bx, parStr+1                                  
    call enterNum
    call makeIntend
    cmp di, 9999
    ja @errorInputStr
    cmp di, 0
    jbe @errorInputStr
    mov str, di
    jmp @firstTryCol

@errorInputCol:
    lea dx, error
    mov ah, 09
    int 21h
    call makeIntend
@firstTryCol:
    lea dx, enterCol
    mov ah, 09
    int 21h
    lea dx, parCol
    mov ah, 0Ah
    int 21h
    lea bx, parCol+1                                  
    call enterNum
    call makeIntend
    cmp di, 0
    jbe @errorInputCol
    mov col, di
    mov ax, str
    imul col 
    jc @errorInputCol
    cmp ax, 9999
    ja @errorInputCol
    mov masSSize, ax
    mov masFSize, ax
    mov masResSize, ax
    
call makeIntend ;Заполнение masF
lea dx, fillMasF
mov ah, 09
int 21h
lea bx, masF    ;Поместить в BX адрес начала массива masF.
mov cx, masFSize
call makeIntend
call fillArray

call makeIntend ;Заполнение masS
lea dx, fillMasS
mov ah, 09
int 21h
lea bx, masS    ;Поместить в BX адрес начала массива masS.
mov cx, masSSize
call makeIntend
call fillArray

call makeIntend
lea dx, resultStr
mov ah, 09
int 21h
call makeIntend
mov cx, masResSize
call taskProc

mov ah, 4ch
int 21h
code ends
end start