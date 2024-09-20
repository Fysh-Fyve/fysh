.globl main

.text
main:
	li	a0, 0xFF000000
	jal	ra, fysh_gpio_write_all
done:
	beqz	zero, done

.data
# L1: .word 27
