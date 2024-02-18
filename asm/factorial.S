.globl _start

# Take the factorial of:
.data
arg: .word 5

# ><number>    ≈ ><{({°>   ><//> b101 = 5
# ><factorial> ≈ ><(({°>   ><//> b001 = 1
#
# ><//> while number > 1
# ><(((@> [><number> o~ ><(({°>]
# ><>
# 	><//> factorial = factorial * number
# 	><factorial> ≈ ><factorial> ♡ ><number> ~
#
# 	><//> number -= 1
# 	<number><< ~
# <><
.text
_start:
	lw	a4, arg  # Number
	li	a5, 1    # Factorial

	li	t0, 1    # load constant into temporary register for comparison
	lui	x31, 0x10
loop:
	sw	a4, 4(x31)
	# while number > 1
	bgt	a4, t0, loop_body

	sw	a5, 0(x31)
halt:
	beq	zero, zero, halt

loop_body:
	mv	a0, a5
	mv	a1, a4
	jal	ra, multiply
done_mul:
	mv	a5, a2
	addi	a4, a4, -1

	j	loop

multiply:
	# Initialize the result to 0
	li	a2, 0     # Initialize the result to 0
# Loop to perform multiplication
mul_loop:
	andi	t1, a1, 1    # Extract the least significant bit of a1
	beqz	t1, skip_add # If the least significant bit is 0, skip adding
	add	a2, a2, a0   # Add a0 to the result if the least significant bit is 1
skip_add:
	slli	a0, a0, 1    # Shift a0 left by 1 (equivalent to multiplying by 2)
	srli	a1, a1, 1    # Shift a1 right by 1 (equivalent to dividing by 2)
	bnez	a1, mul_loop # Repeat the loop if a1 is not zero
	# The result is in register a2
	ret

