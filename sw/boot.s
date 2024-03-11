.globl _start

.text
_start:
	# TODO: Do more initialization here.
	# (e.g.) Stack, thread, and global pointer initialization,  etc.
	li	sp, 0x12000
	call	main
done:
	beqz	zero, done
