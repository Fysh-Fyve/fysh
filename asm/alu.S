.globl _start

.text
_start:
	li	t0, 10
	addi	t0, t0, -1
	lui	x31, 0x10
	sw	t0, 4(x31)
done:
	beqz	zero, done

.data
# L1: .word 27
