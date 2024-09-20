.globl main

.text
main:
	lui	x15, 0x10
	auipc	x2, 0x12345
	addi	x1, x2, 10
	srai	x20, x15, 2
	add	x1, x2, x15
	sub	x1, x20, x2
	sw	x2, 8(x15)
	lw	x16, 8(x15)
	jal	x1, skip_nop
	.word 0x12345678
skip_nop:
	jal	x4, bad_beq
	.word 0xDEADBEEF
bad_beq:
	beq	x0, x15, not_taken
good_beq:
	beq	x2, x16, multiply
	nop
	nop
	nop
	nop
	nop
	nop
not_taken:
	nop
multiply:
	# Load two integers into registers
	li	a0, 2    # Load the first integer into register a0
	li	a1, 2    # Load the second integer into register a1

	# Initialize the result to 0
	li	a2, 0     # Initialize the result to 0
# Loop to perform multiplication
mul_loop:
	andi	a3, a1, 1    # Extract the least significant bit of a1
	beqz	a3, skip_add   # If the least significant bit is 0, skip adding
	add	a2, a2, a0   # Add a0 to the result if the least significant bit is 1
skip_add:
	slli	a0, a0, 1   # Shift a0 left by 1 (equivalent to multiplying by 2)
	srli	a1, a1, 1   # Shift a1 right by 1 (equivalent to dividing by 2)
	bnez	a1, mul_loop  # Repeat the loop if a1 is not zero
done:
	# The result is in register a2
	lui	x31, 0x10
	sw	a2, 0(x31)
halt:
	# we can actually execute arbitrary words so we really would not need
	# to do additional work on the assembler :^)
	# .word 0x00000063 # same as the instruction below
	beq	x0, x0, halt

.data
# L1: .word 27
