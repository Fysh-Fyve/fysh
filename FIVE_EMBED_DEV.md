# RISC-V Instruction Set Manual

## ISA Overview

3 categories - _standard_, _reserved_, _custom_.

Extensions - _standard_

- I - base integer ISA
  - integer computational instructions
  - integer loads
  - integer stores
  - control-flow instructions
- M - integer multiplication
  - multiplies and divides in the registers
- A - atomic
  - Atomically read, modify, and write memory
- F - single-precision floats
  - floating-point registers
  - single-precision computational instructions
  - single-precision loads and stores
- D - double-precision floats
  - expands the floating-point registers
  - adds double-precision computational instructions, loads, and stores
- C - compressed
  - provides narrower 16-bit forms of instructions

## Memory

Single-byte addressable, 2^XLEN bytes

Circular, so 2^XLEN - 1 is adjacent to the byte at address 0. Overflows are also
ignored so memory address computations wrap around module 2^XLEN.

- Word - 32 bits (4 bytes)
- Halfword - 16 bits (2 bytes)
- Doubleword - 64 bits (8 bytes)
- Quadword - 128 bits (16 bytes)

Address space can be vacant, contain _main_ memory, or one or more I/O devices.

Reads and writes of I/O devices may have visible side effects, but accesses to
main memory cannot. (what does this mean??)

- The execution environment determines which ones are accessible... so we good?
- How do exceptions work for illegal access doe.
- Instruction fetch can even be different from the fetches for load/store! Damn

## Base Instruction-Length Encoding

- 32-bit instructions, must be 32-bit aligned in memory
- When using C extension, 16-bit parcels must be aligned on 16-bit boundaries

## Exceptions, Traps, Interrupts

- I am so confused, maybe another time

# RV32I Base Integer Instruction Set, Version 2.1

## Programmer's Model for Base Integer ISA

- 32 `x` registers, 32-bits wide
- `x0` is hardwired to zero

- PC - additional register that holds the address of the current instruction

- Standard software calling convention
  - x1 - return address for a call
  - x5 - alternate link register
  - x2 - stack pointer

## Base Instruction Formats

- 4 core instruction formats (R/I/S/U)
  - R has no immediate value.
  - I has the low 12 bits of the sign-extended immediate value in the high 12
    bits of the instruction.
  - S is like I, but the lower 5 bits is in the `rd` spot to make room for
    `rs2`.
  - U has the high 20 bits of the immediate value in the high 20 bits. the lower
    12 bits are zeroed.
- instruction-address-misaligned exception is generated on a taken branch or
  unconditional jump if the target address is not four-byte aligned.
  - Reported on the branch/jump instruction, not on the target instruction

![](./assets/rv32_01.png)

- RISC-V keeps the `rs1`, `rs2`, and `rd` registers in the same position in all
  formats
- Sign bit is always in bit 31 to speed up sign extension

## Immediate Encoding Variants

- B is like S, but shifted left by 1. This means the 12 bit replaces the 1 bit.
- J is like U, but crazy. I don't wanna bother to explain anything other than
  the fact that its least significant bit is also 0 like the B-type. It's also
  become the low 20 bits (shifted left by 1) instead of the high 20 bits.

## Integer Computational Instructions

Either encoded in I-type (register-immediate) or R-type (register-register).

No arithmetic instructions cause arithmetic exceptions (stuff just overflows
silently).

- Overflows aren't included because overflow checks can be done with branches.
- Okay this actually sucks

### Integer Register-Immediate Instructions

ADDI/SLTI\[U\]

TODO:
[Continue](https://five-embeddev.com/riscv-isa-manual/latest/rv32.html#integer-register-immediate-instructions)
