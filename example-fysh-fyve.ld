OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
ENTRY(_start)

MEMORY
{
  INST (rx) : ORIGIN = 0x0, LENGTH = 0x400
  DATA (rx) : ORIGIN = 0x400, LENGTH = 0x80
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
