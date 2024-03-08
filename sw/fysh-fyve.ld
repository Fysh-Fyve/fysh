/**
 * Linker script, might need to change the ORIGIN of the DATA part once INST
 * section gets too big :)
 */

/* No fysh-fyve unfortunately :( */
OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
ENTRY(_start)

MEMORY
{
  INST (rx) : ORIGIN = 0x0, LENGTH = 0x200
  /* Technically should be rwx but we're raw-dogging data into the ROM */
  DATA (rx) : ORIGIN = 0x200, LENGTH = 0x80
}

SECTIONS
{
  .text :
  {
    *(.text)
  }> INST

  .data :
  {
    *(.data)
  }> DATA
}

