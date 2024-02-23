.globl _start

.text
_start:
	jalr	ra, 0x10
done:
	beqz	zero, done
