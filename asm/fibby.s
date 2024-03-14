.globl main

.text
main:
	addi	sp, sp, -16
	sw	ra, 0xc(sp)
	li	a0, 5
	call	fib
	lui	x31, 0x10
	sw	a0, 4(x31)
	lw	ra, 0xc(sp)
	addi	sp, sp, 16
	ret
fib:
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	sw	s1, 4(sp)                       # 4-byte Folded Spill
	sw	s2, 0(sp)                       # 4-byte Folded Spill
	li	a1, 2
	mv	s0, a0
	li	s1, 0
	bltu	a0, a1, .LBB4_3
# %bb.1:
	li	s2, 1
.LBB4_2:                                # =>This Inner Loop Header: Depth=1
	addi	a0, s0, -1
	call	fib
	addi	s0, s0, -2
	add	s1, a0, s1
	bltu	s2, s0, .LBB4_2
.LBB4_3:
	add	a0, s0, s1
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	lw	s1, 4(sp)                       # 4-byte Folded Reload
	lw	s2, 0(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret

.data
# L1: .word 27
