# Concept of Operation

The high-level operation of the RISC-V FPGA-based CPU and Language is
illustrated by the following user stories and use cases.

## User Stories

### Writing a Compiler

Our capstone project is focused on developing an esoteric programming language
[@esolang] - Fysh. Fysh is designed for RISC-V architecture. Inspired by leaders
in the esoteric world, languages like brainfuck [@brainfuck] and Chicken
[@chicken], Fysh aims to introduce a unique syntax and a hardware noise based
random number generator. Our goal is to combine our technical skills and
creativity to create a language that is not only fun but also expands our
experience and knowledge in compiler design. This project aims towards exploring
new possibilities in programming language design.

### Learning about RISC-V ISA

We are developing a RISC-V CPU with a custom instruction, highlighting RISC-V's
extensibility. By employing VHDL for the CPU and programming a Zybo board, the
project becomes accessible to all ECE students. With a softcore microprocessor
and a compiler included, we are creating a comprehensive full-stack computer
engineering project, providing a valuable learning tool for other students.

## Use Cases

The use case diagram below (Figure \ref{fig:use-case}) summarizes the use cases
for this project. The only actor in this system is the Computer Engineering
student that intends to run a program written in Fysh on the RISC-V CPU. The
four main use cases that can be invoked by the Computer Engineering student are
"Initialize Chyp" (Table \ref{Tab:UC-001}), "Compyle Fysh" (Table
\ref{Tab:UC-002}), "Program Board" (Table \ref{Tab:UC-003}), and "Run Fysh"
(Table \ref{Tab:UC-004}).

- Initialize Chyp - program the FPGA with the softcore CPU.
- Compyle Fysh - compile the Fysh program into a binary.
- Program Board - load the compiled binary into the development board's
  read-only memory (ROM).
- Run Fysh - Turn on the CPU on the development board.

\input{tex/use-case}

\input{tex/uc-001}

\input{tex/uc-002}

\input{tex/uc-003}

\input{tex/uc-004}
