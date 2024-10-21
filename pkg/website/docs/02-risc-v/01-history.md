# History of the Fysh-Fyve CPU

The goal of the Fysh-Fyve CPU project is to have a publicly available VHDL
implementation of a RISC-V CPU for the
[Zybo Z7 development board](https://digilent.com/reference/programmable-logic/zybo-z7/start)
that can be used by future ECE students at the University of Alberta.

## Base Design

Our overall CPU design is mostly borrowed from a Basic Computer Design video on
YouTube[^1]. However, the implementation for each component was still up to us.

Some of the components were trivial to implement, like the ALU, program counter,
register files, and instruction registers.

---

[^1]: [Basic Computer Design (part 2), A Simple RISC-V RV32I CPU](https://www.youtube.com/watch?v=zW2Pmki81ow)
