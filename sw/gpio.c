#include <stdint.h>

uint32_t *gpio_address = (uint32_t *)0xDEADBEEF;

uint32_t fysh_gpio_read(const uint32_t pin) {
  return (*gpio_address >> pin) & 1;
}

uint32_t fysh_gpio_read_all() { return *gpio_address; }

void fysh_gpio_write_all(const uint32_t value) { *gpio_address = value; }

void fysh_gpio_write(const uint32_t pin, const uint32_t value) {
  // Will there be a timing issue for this
  const uint32_t curr_val = *gpio_address;
  const uint32_t bit = (1 << pin);
  *gpio_address = !value ? curr_val & ~bit : curr_val | bit;
}
