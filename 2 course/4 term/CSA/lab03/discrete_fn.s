.globl f

.data
case1:   .asciiz "f(-4) should be -6, and it is: "
case2:   .asciiz "f(-3) should be 46, and it is: "
case3:   .asciiz "f(-2) should be -46, and it is: "
case4:   .asciiz "f(-1) should be 25, and it is: "
case5:   .asciiz "f(0) should be 30, and it is: "
case6:   .asciiz "f(1) should be 48, and it is: "
case7:   .asciiz "f(2) should be 5, and it is: "

output: .word   -6, 46, -46, 25, 30, 48, 5

.text
main:
    la a0, case1 
    jal print_str 
    li a0, -4
    la a1, output
    jal f     
    jal print_int
    jal print_newline

    la a0, case2
    jal print_str
    li a0, -3
    la a1, output
    jal f                
    jal print_int
    jal print_newline

    la a0, case3
    jal print_str
    li a0, -2
    la a1, output
    jal f               
    jal print_int
    jal print_newline

    la a0, case4
    jal print_str
    li a0, -1
    la a1, output
    jal f               
    jal print_int
    jal print_newline

    la a0, case5
    jal print_str
    li a0, 0
    la a1, output
    jal f                
    jal print_int
    jal print_newline

    la a0, case6
    jal print_str
    li a0, 1
    la a1, output
    jal f               
    jal print_int
    jal print_newline

    la a0, case7
    jal print_str
    li a0, 2
    la a1, output
    jal f                
    jal print_int
    jal print_newline

    li a0, 10
    ecall

f:
    # FIXME
    # YOUR CODE GOES HERE!
    addi a0, a0, 4  #make position num from input
    slli a0, a0, 2 #create output adress from position num (left shift)
    add a1, a1, a0 #add output adress to massive adress
    lw a0, 0(a1) #take an output num
    jr ra               

print_int:
    mv a1, a0
    li a0, 1
    ecall
    jr    ra

print_str:
    mv a1, a0
    li a0, 4 
    ecall
    jr    ra

print_newline:
    li a1, '\n'
    li a0, 11 
    ecall
    jr    ra