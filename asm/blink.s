.globl main

.text
main:
	li	x31, 0xDEADBEEF
	li	a5, 0x01000000
	li	a4, 0x01000000
	li	a0, 0
	li	a3, 5
loop:
	beqz	a0, toggle
	addi	a0, a0, -1
	j	loop
toggle:
	lw	a0, delay
	xor	a5, a5, a4
	sw	a5, 0(x31)
	addi	a3, a3, -1
	beqz	a3, loop
	j	loop
done:
	beqz	zero, done

.data
delay: .word 1
