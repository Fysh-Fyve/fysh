# Concept of Operation

The high-level operation of the RISC-V FPGA-based CPU and Language is
illustrated by the following user stories and use cases.

## User Stories

### Writing a Compiler

Upon receiving the project list for this semester's capstone project, we were
excited to see that there is a project described as "Likely the most difficult
project on our list": a native C compiler for a single board computer with a
custom CPU and instruction set. It was to our disappointment that the computer
did not yet have an operating system, rendering the project infeasible and
impractical.

However, we insisted on working on a compiler. This time, we are targeting
RISC-V[@riscv], an open standard ISA that is gaining popularity in the industry.
It was initially stated in the proposal that we are taking inspiration from
modern languages like Rust, Zig, or Go[@ppr], but we have also decided to
unleash our creativity and make our programming language esoteric[@esolang].

### Learning about RISC-V ISA

We are also curious about the internals of real-world CPUs. We have only
encountered a "toy" VHDL implementation of a CPU in ECE 410, our digital logic
design course. Our initial idea was to run the compiled program written in our
esoteric programming language on an ESP-32 C3 MCU[@esp32]. However, we are
required to have a hardware aspect to our project.

Because of this, we decided to implement a RISC-V CPU ourselves with a custom
CPU instruction to showcase the extensibility of RISC-V. Implementing the CPU in
VHDL and programming a Zybo board means that the project can be used by all ECE
students. With a softcore microprocessor and a compiler, we have a real
full-stack computer engineering project that we can be proud of and can
potentially aid in the learning of other computer engineering students.

## Use Cases

\input{tex/use-case}

\input{tex/uc-001}

\input{tex/uc-002}

\input{tex/uc-003}

\input{tex/uc-004}
