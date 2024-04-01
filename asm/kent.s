.globl main

.text
main:
	call	counter_read
	lui	x31, 0x10
	sw	a0, 4(x31)
done:
	beqz	zero, done

.data
# L1: .word 27

