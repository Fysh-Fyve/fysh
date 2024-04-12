#include <stdint.h>

uint32_t *counter_address = (uint32_t *)0xDEADBEE4;
uint32_t *mode_address = (uint32_t *)0xDEADBEE8;
uint32_t *gpio_address = (uint32_t *)0xDEADBEEF;

uint32_t fysh_gpio_read(const uint32_t pin) {
  return (*gpio_address >> pin) & 1;
}

// uint32_t t = 0;
// uint32_t rand() { return (t = 69069 * t + 69069); }
// void rand_init(uint32_t seed) { t = seed; }

uint32_t fysh_gpio_read_all() { return *gpio_address; }

void fysh_gpio_write_all(const uint32_t value) { *gpio_address = value; }

void pin_mode(const uint32_t pin, const uint32_t value) {
  const uint32_t curr_val = *mode_address;
  const uint32_t bit = (1 << pin);
  *mode_address = !value ? curr_val & ~bit : curr_val | bit;
}

void fysh_gpio_write(const uint32_t pin, const uint32_t value) {
  // Will there be a timing issue for this
  const uint32_t curr_val = *gpio_address;
  const uint32_t bit = (1 << pin);
  *gpio_address = !value ? curr_val & ~bit : curr_val | bit;
}

// uint32_t counter_read() { return *counter_address; }

// uint32_t get_seg(const uint32_t val) {
//   switch (val) {
//     // clang-format off
//     case 0x0: return 0b0111111;
//     case 0x1: return 0b0000110;
//     case 0x2: return 0b1011011;
//     case 0x3: return 0b1001111;
//     case 0x4: return 0b1100110;
//     case 0x5: return 0b1101101;
//     case 0x6: return 0b1111101;
//     case 0x7: return 0b0000111;
//     case 0x8: return 0b1111111;
//     case 0x9: return 0b1101111;
//     case 0xA: return 0b1110111;
//     case 0xB: return 0b1111100;
//     case 0xC: return 0b0111001;
//     case 0xD: return 0b1011110;
//     case 0xE: return 0b1111001;
//     case 0xF: return 0b1110001;
//     default:  return 0;
//     // clang-format on
//   }
// }

void draw_fysh(uint32_t dy, uint32_t dx);

void draw_frame(uint32_t dy, uint32_t dx) {
  for (int i = 0; i < 100; i++) {
    draw_fysh(dy, dx);
  }
}
