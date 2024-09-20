.globl main

.text
main:

branch_beq:
	li	t0, 10
	li	t1, 10
	beq	t0, t1, branch_bne
	j	bad
branch_bne:
	li	t0, 10
	li	t1, 11
	bne	t0, t1, branch_blt
	j	bad
branch_blt:
	blt	t0, t1, branch_bge
	j	bad
branch_bge:
	bge	t1, t0, branch_bltu
	j	bad
branch_bltu:
	bltu	t0, t1, branch_bgeu
	j	bad
branch_bgeu:
	bgeu	t1, t0, skip_bne
	j	bad

skip_beq:
	li	t0, 10
	li	t1, 11
	beq	t0, t1, bad
skip_bne:
	li	t0, 10
	li	t1, 10
	bne	t0, t1, bad
skip_blt:
	li	t0, 10
	li	t1, 11
	blt	t1, t0, bad
skip_bge:
	bge	t0, t1, bad
skip_bltu:
	bltu	t1, t0, bad
skip_bgeu:
	bgeu	t0, t1, bad

# Good will halt in fysh-fyve
good:
	beqz	zero, good
# Bad will loop infinitely in fysh-fyve
bad:
	nop
	beqz	zero, bad

.data
# L1: .word 27
