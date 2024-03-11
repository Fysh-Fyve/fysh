	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p1"
	.file	"<stdin>"
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
	li	a0, 1
	call	fysh_gpio_write_all
	call	fysh_gpio_read_all
	li	a1, 1
	li	a0, 0
	call	fysh_gpio_write
	li	a0, 0
	li	a1, 0
	call	fysh_gpio_write
	li	a1, 1
	li	a0, 0
	call	fysh_gpio_write
	li	a0, 0
	li	a1, 0
	call	fysh_gpio_write
.LBB0_1:                                # %loop_cond
                                        # =>This Inner Loop Header: Depth=1
	j	.LBB0_1
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
