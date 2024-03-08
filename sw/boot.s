.globl _start

.text
_start:
	# TODO: Do more initialization here.
	# (e.g.) Stack, thread, and global pointer initialization,  etc.
	jal	ra, main
done:
	beqz	zero, done
