# Final Presentation

## First minute

- Team intro & sponsors

$1: Hello everyone, we are Fysh-Fyve, although only consisting of three members.
I'm $1.

$2: I'm $2.

$3: I'm $3.

$1: Our project, titled "RISC-V FPGA-Based CPU and Programming Language",
started as a simple compiler project that has since evolved to become what one
would call a Full-stack Hyperpolyglot Gigachad Alpha Organism Free and Open
Source Software Capstone Project.

- What is the project? and how did it turn out

$2: While this project is not a typical product, it serves as a amalgamation of
Computer Engineering concepts that we have learned throughout the program such
as computer architecture, compiler design, and development tooling. It also aims
to expand these concepts to use industry-standard frameworks such as the the
RISC-V instruction set architecture, the LLVM compiler infrastructure, and the
Language Server Protocol (LSP).

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
