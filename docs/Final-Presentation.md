# Final Presentation

## First minute

<!-- 1 minute intro showing the poster -->

- Team intro & sponsors

Hello we are "RISC-V FPGA-Based CPU and Programming Language" (team 11) or Fysh-Fyve for short

<!-- Mention teammates and client (2) -->

$1: I'm $1.

$2: I'm $2.

$3: I'm $3.

$2: We would like to thank our sponsor, Steven Knudsen, for his support and guidance throughout the project.

$1: We started as a compiler project for eleven engineering, but there was no operating system to run the compiled code. So we decided to privot. Meet Fysh-Fyve!

- What does Fysh-Fyve really mean?

<!-- Define project (5 subjective) -->

$2: Fysh-Fyve is two projects swimming side by side. The first of which is a fish themed programming language called Fysh. The second is an FPGA RISC-V CPU that runs Fysh programs.

Fysh is esoteric at its core. It's goal is to create a fun, educational, and simple to use programming language. Every compontent of the language symbolizes a real world concept. Like fysh scales representing their value, and tadpoles swimming towards bigger fysh.

The second is an FPGA RISC-V CPU. It's designed to be simple and just barely able to run Fysh programs. It can be used as a learning tool for students and has a custom instruction for random number generation we call Grilled Fysh. It uses the voltage noise from the FPGA to generate a random number.

$2: While this project is not a typical product, it serves as a amalgamation of
Computer Engineering concepts that we have learned throughout the program such
as computer architecture, FPGA design, development tooling, and being thrown into an ocean (of work) and expected to swim. 
These skills were essenctial in developing the Fysh-Fyve project.

Fysh-Fyve aims to expand these concepts by using industry-standard frameworks such as the
RISC-V instruction set architecture, LLVM compiler infrastructure,
Language Server Protocol (LSP).

<!-- Describe project expectations & outcome (10 subjective) -->

It can also serve as a reminder to future Computer Engineering students that
maybe there is such a thing as too much fun.

Before we start with the demonstration, we would like to thank our sponsor
Steven Knudsen, for even greenlighting this project, and for the myriad of Fysh
puns.

## Prototype Demonstration

$3: Putting the various components of our project together, we would get this
end result:

\<Show two stationary Fysh in the 8x8 LED matrix\>

To see the process of getting these LEDs to light up, let's hop on to our dev
machine.

<!-- Yeah, the 64x64 LED matrix is a work in progress. -->
<!---->
<!-- \<Show Swimming Fysh in the 64x64 LED matrix\> -->
<!---->
<!-- \<Pan to Raspberry Pi driving the 64x64 LED Matrix\> -->
<!---->
<!-- It's driven by a Raspberry Pi using an existing library. -->

<!-- 1 minute intro showing the poster -->
<!-- Mention teammates and client (2) -->
<!-- Define project (5 subjective) -->
<!-- Describe project expectations & outcome (10 subjective) -->
<!---->
<!-- 9-14 minute demonstration and presentation -->
<!-- Effective demo (20 subjective) -->
<!-- Mention what worked and didn’t work (4) -->
<!-- Mention future work (5 subjective) -->
<!-- Conclusion (4 subjective) -->
<!-- Each team member must speak -->
<!---->
<!-- Total marks available : 50 -->

### Coding in Fysh

\<Show the pinout here\>

To start, let's look at the pre-defined pinout for the LED matrix. We have the
first 3 bits mapped to the column index, the next 3 bits to the row, and the
last bit as the output enable pin.

\<Show the ASCII matrix of Fysh\>

This matrix shows which LEDs we want to light up, and their indices. So for the
right-facing fysh, it's (0,0), (0,2), (0,3), (1,1), (1,4), (2,0), (2,2), and
(2,3). For the left-facing fysh it's (4,4), (4,5), (4,7), (5,3), (5,6), (6,4),
(6,5), and (6,7). Let's copy these coordinates and paste them to a new file.

#### Output to GPIO pins

Let's start by trying to draw a single pixel. To write into the GPIO pins, we
use the anchor out operator. Starting from the highest bit, we want the 7th bit
to be always high. And for the next 3 bits, we only want the first 3 bits of
`row`, so we mask it with 7, then we shift that left by 3. For the last 3 bits,
we also want to mask `col`.

#### Subroutine

We can refactor this state into a subroutine called pixel for convenience.

#### Create while loop

Now to define the main program, we just want to draw two fysh (proceed to
program).

### Compyling Fysh

Now that we're done programming, let's compile this and flash it to the
Fysh-Fyve CPU.

TODO: Show diagram

### Build VHDL project

TODO: Show code?? Idk

#### RISC-V CPU

- Architecture
- How the memory is laid out?
- Random Fysh

### Discussion

- what went right (of course)
- what went wrong
- where we went above and beyond (language server)
