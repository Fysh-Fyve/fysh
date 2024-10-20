	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p1"
	.file	"simple-matrix.fysh"
	.globl	set_pixel                       # -- Begin function set_pixel
	.p2align	2
	.type	set_pixel,@function
set_pixel:                              # @set_pixel
	.cfi_startproc
# %bb.0:                                # %entry
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	.cfi_offset ra, -4
	.cfi_offset s0, -8
	slli	a0, a0, 29
	srli	a0, a0, 26
	andi	a1, a1, 7
	or	a0, a1, a0
	addi	s0, a0, 128
	mv	a0, s0
	call	fysh_gpio_write_all
	mv	a0, s0
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end0:
	.size	set_pixel, .Lfunc_end0-set_pixel
	.cfi_endproc
                                        # -- End function
	.globl	draw_fysh                       # -- Begin function draw_fysh
	.p2align	2
	.type	draw_fysh,@function
draw_fysh:                              # @draw_fysh
	.cfi_startproc
# %bb.0:                                # %entry
	addi	sp, sp, -32
	.cfi_def_cfa_offset 32
	sw	ra, 28(sp)                      # 4-byte Folded Spill
	sw	s0, 24(sp)                      # 4-byte Folded Spill
	sw	s1, 20(sp)                      # 4-byte Folded Spill
	sw	s2, 16(sp)                      # 4-byte Folded Spill
	sw	s3, 12(sp)                      # 4-byte Folded Spill
	sw	s4, 8(sp)                       # 4-byte Folded Spill
	.cfi_offset ra, -4
	.cfi_offset s0, -8
	.cfi_offset s1, -12
	.cfi_offset s2, -16
	.cfi_offset s3, -20
	.cfi_offset s4, -24
	mv	s0, a1
	mv	s1, a0
	call	set_pixel
	addi	s2, s0, 2
	mv	a0, s1
	mv	a1, s2
	call	set_pixel
	addi	s3, s0, 3
	mv	a0, s1
	mv	a1, s3
	call	set_pixel
	addi	s4, s1, 1
	addi	a1, s0, 1
	mv	a0, s4
	call	set_pixel
	addi	a1, s0, 4
	mv	a0, s4
	call	set_pixel
	addi	s1, s1, 2
	mv	a0, s1
	mv	a1, s0
	call	set_pixel
	mv	a0, s1
	mv	a1, s2
	call	set_pixel
	mv	a0, s1
	mv	a1, s3
	call	set_pixel
	lw	ra, 28(sp)                      # 4-byte Folded Reload
	lw	s0, 24(sp)                      # 4-byte Folded Reload
	lw	s1, 20(sp)                      # 4-byte Folded Reload
	lw	s2, 16(sp)                      # 4-byte Folded Reload
	lw	s3, 12(sp)                      # 4-byte Folded Reload
	lw	s4, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end1:
	.size	draw_fysh, .Lfunc_end1-draw_fysh
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	.cfi_offset ra, -4
.LBB2_1:                                # %loop_cond
                                        # =>This Inner Loop Header: Depth=1
	li	a0, 1
	li	a1, 0
	call	draw_frame
	li	a0, 1
	li	a1, 1
	call	draw_frame
	li	a0, 1
	li	a1, 2
	call	draw_frame
	li	a0, 1
	li	a1, 3
	call	draw_frame
	li	a0, 1
	li	a1, 4
	call	draw_frame
	li	a0, 1
	li	a1, 5
	call	draw_frame
	li	a0, 1
	li	a1, 6
	call	draw_frame
	li	a0, 1
	li	a1, 7
	call	draw_frame
	j	.LBB2_1
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
