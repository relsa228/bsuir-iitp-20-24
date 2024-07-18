global  toProtectedMode
global  torealmode
section .text

toProtectedMode:
    int 21h
    ret

torealmode:
    mov     rax, rcx
    cmp     rax, rdx
    cmove   rax, rdx
    cmp     rax, r8
    cmove   rax, r8
    ret