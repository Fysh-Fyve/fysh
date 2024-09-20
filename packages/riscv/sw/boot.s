.globl _start
.globl fysh_grilled

.text
_start:
	# TODO: Do more initialization here.
	# (e.g.) Stack, thread, and global pointer initialization,  etc.
	li	sp, 0x12000
	call	main
done:
	beqz	zero, done
fysh_grilled:
	# fysh a0 (store random number into a0)
	.word 0x0000056b
	ret
