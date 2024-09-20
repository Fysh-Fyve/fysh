.globl main

.text
main:
	li	x31, 0xDEADBEEF
	li	a5, 0x01000000
	li	a4, 0x01000000
loop:
	sw	a5, 0(x31)
	xor	a5, a5, a4
	j	loop
done:
	beqz	zero, done

.data
delay: .word 1
