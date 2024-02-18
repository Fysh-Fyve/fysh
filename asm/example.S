.globl _start

.text
_start:
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
	# idk what this is but it's supposed to skip again to bad_beq
	jalr	x4, 48(x0)
	.word 0xDEADBEEF
bad_beq:
	beq	x0, x15, not_taken
good_beq:
	beq	x2, x16, halt
	nop
	nop
	nop
	nop
	nop
	nop
not_taken:
	nop
halt:
	# we can actually execute arbitrary words so we really would not need
	# to do additional work on the assembler :^)
	# .word 0x00000063 # same as the instruction below
	beq	x0, x0, halt

.data
# L1: .word 27
