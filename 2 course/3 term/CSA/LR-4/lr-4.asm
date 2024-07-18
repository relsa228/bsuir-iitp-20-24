.model small
.stack 256

data segment

diBuff  dw  0
cxBuff  dw  0

enterStr db 'Enter string: $'
resultStr db 'Result: $'
vowels db 'AaEeYyUuIiOo$'
consonants db 'QqWwRrTtPpSsDdFfGgHhJjKkLlZzXxCcVvBbNnMm$'
indent  db '', 0Dh, 0Ah, '$'

parStr label byte
maxlenStr db 100
actlenStr db ?
fldStr db 100 dup('$')

result db ($-fldStr) dup ('$')

data ends

code segment
assume cs:code, ds:data

findVowels proc near    ;символ для проверки должен лежать в al, результат проверки (0 или 1) записывается в ax    		                                 		
cld            		
mov  cx, 13    		
lea  di, vowels     
repne  scasb 
je @vowTrue

@vowFalse:
mov ax, 0
ret

@vowTrue:
dec di
mov ax, 1
ret
findVowels endp



findConsonants proc near    ;символ для проверки должен лежать в al, результат проверки (0 или 1) записывается в ax    		                                 		
cld            		
mov  cx, 41    		                              		
lea  di, consonants     
repne  scasb 
je @constTrue

@constFalse:
mov ax, 0
ret

@constTrue:
dec di
mov ax, 1
ret
findConsonants endp



taskProc proc
lea bx, parStr+1    ;ищем длину строки и заносим её в cx для цикла
mov cx, [bx] 
xor ch, ch

mov si, 0           ;ставим счётчик итерации по строке (i) для источника
mov bp, 0           ;ставим счётчик итерации по строке (j) для результата
mov di, 0

@taskLoop:
mov  ax, ds         ;подготовка к вызову функции 
mov  es, ax 
mov al, fldStr[si]         ;окончание подготовки
mov diBuff, di
mov cxBuff, cx
call findVowels
mov di, diBuff
mov cx, cxBuff
cmp ax, 1
je @volwels

mov  ax, ds         ;подготовка к вызову функции 
mov  es, ax 
mov al, fldStr[si]         ;окончание подготовки
mov diBuff, di
mov cxBuff, cx
call findConsonants
mov di, diBuff
mov cx, cxBuff
cmp ax, 1
je @consonants

cmp al, ''''
je @apos

mov al, fldStr[si]
cmp al, ' '
je @space

@default:
mov al, fldStr[si]
mov result[bp], al
inc bp
inc di
jmp @end

@midP:
jmp @taskLoop

@volwels:
mov ax, di
mov bx, 2
xor dx, dx
div bx
cmp dx, 1
jne @default
inc di
jmp @end

@consonants:
mov ax, di
mov bx, 2
xor dx, dx
div bx
cmp dx, 1
je @default

@evenCons:
mov al, fldStr[si]
mov result[bp], al
inc bp
mov al, fldStr[si]
mov result[bp], al
inc bp
inc di
jmp @end

@apos:
mov al, fldStr[si]
mov result[bp], al
inc bp
jmp @end

@space:
mov result[bp], ' '
inc bp
mov di, 0
jmp @end

@end:
inc si
loop @midP

ret
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

lea dx, enterStr                                     
mov ah, 09
int 21h

lea dx, parStr
mov ah, 0Ah        
int 21h

call taskProc
call makeIntend

lea dx, resultStr
mov ah, 09
int 21h

lea dx, result
int 21h

mov ah, 4ch
int   21h
code ends
end start