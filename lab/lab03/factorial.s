.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial
    
    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result
    
    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    beq a0, x0, exit_fac
    addi sp, sp, -8
    sw ra, 4(sp)
    sw a0, 0(sp)
    
    addi a0, a0, -1
    jal ra, factorial
    lw s0, 0(sp)
    lw ra, 4(sp)
    mul a0, a0, s0
    addi sp, sp, 8
    jr ra
    
      
exit_fac:
	addi a0, x0, 1
    jr ra
    
    
