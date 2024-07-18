.globl iterative
.globl recursive

.data
n: .word 8

.text
main:
    la t0, n
    lw a2, 0(t0) # counter
    
    jal ra, tester

	add a2, x0, a1 #save result for recursive
    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result for a0 (iterative)

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline
    
    add a1, x0, a2 #return recursive result
    addi a0, x0, 1
    ecall # Print Result for a1 (recursive)

    addi a0, x0, 10
    ecall # Exit

tester:
	addi sp, sp, -4
    sw ra, 4(sp)
	jal ra, iterative
    
    ADDI t1, x0, 1 #null point of progression for rec
    ADDI t2, x0, 0 #counter for rec
    
    addi sp, sp, -4
    sw ra, 4(sp)
	jal ra, recursive
    
	lw ra, 8(sp)
    addi sp, sp, 8
    jalr ra #tester exit
    

iterative:
    ADDI t1, x0, 1 #null point of progression for iter
    ADDI t2, x0, 0 #counter for iter
    
    loop:
    BEQ a2, t2, exit_iter
    ADDI t1, t1, 3
    ADDI t2, t2, 1
    j loop
    
    exit_iter:
    ADD a0, x0, t1 #result
    jalr ra
    
recursive:
    addi sp, sp, -4
    sw ra, 4(sp)
    
	BEQ a2, t2, exit_rec
    ADDI t1, t1, 3
    ADDI t2, t2, 1
    
	jal ra, recursive
    
    exit_rec:
    ADD a1, x0, t1 #result
    lw ra, 4(sp)
    addi sp, sp, 4
    jalr ra
