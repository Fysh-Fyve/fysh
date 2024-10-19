#include <stdint.h>

uint32_t *gpio_address = (uint32_t *)0xDEADBEEF;

uint32_t fysh_gpio_read_all() { return *gpio_address; }

void fysh_gpio_write_all(const uint32_t value) { *gpio_address = value; }

/* And other functions and address definitions... */
