.model small
.stack 256

data segment
a   dw   1
b   dw   2
c   dw   3
d   dw   4
max   dw   0
result   dw   0

data ends

code segment
assume cs:code, ds:data
start:
        mov ax, data
        mov ds, ax
        mov ax, a
        imul a
        imul a
        imul a              
        mov bx, b
        cmp ax, bx                                      ; первое сравнение (pow(a,4)>b)
        jg @biggerFirstCMP
        jle @notBiggerFirstCMP

        @biggerFirstCMP:                                ; первая ветка первого сравнения  (pow(a,4)>b)
            mov ax, c
            imul b
            mov bx, ax
            mov ax, d
            idiv b
            cmp ax, bx                                  ; второе сравнение (c*b==d/b)
            je @equalSecondCMP
            jle @notEqualSecondCMPStart

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
                    mov bx, ax
                    mov ax, max
                    idiv bx
                    mov result, ax
                    jmp @exit                          ; result = max(a,b,c)/(pow(a,2)-b)

        @notBiggerFirstCMP:                            ; вторая ветка первого сравнения (pow(a,4)<=b)
            mov ax, c
            imul c
            imul c
            mov bx, b
            add ax, bx
            mov result, ax
            jmp @exit                                  ; result = pow(c,3) + b

    @exit:
        mov ax, result
        mov ah, 4ch
        int   21h
code ends
    end start