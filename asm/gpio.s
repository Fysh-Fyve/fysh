.globl main

.text
main:
	li	x31, 0xDEADBEEF
	li	t0, 0xFF
	sw	t0, 0(x31)
done:
	beqz	zero, done

.data
# L1: .word 27
