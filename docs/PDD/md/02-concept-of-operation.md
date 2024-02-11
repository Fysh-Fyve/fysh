# Concept of Operation

The high-level operation of the RISC-V FPGA-based CPU and Language is
illustrated by the following user stories and use cases.

## User Stories

<!-- Maybe have a talk about how my year had 68k? -->
<!-- And only the year after that did we have ARM for assembly -->
<!-- This project is kind of a way for us to keep ECE moving forward to modernity -->

<!-- Have at most 3 paragraphs per user story, preferably one -->

Upon receiving the project list for this semester's capstone project, we were
excited to see that there is a project described as "Likely the most difficult
project on our list", a native C compiler for a single board computer with a
custom CPU and instruction set. It was to our disappointment that the computer
did not yet have an operating system, rendering the project infeasible and
impractical.

However, we insisted on still working on a compiler, this time targeting
RISC-V[@riscv], an open standard ISA that is gaining popularity. We are also
curious about the internals of real-world CPUs, only having encountered a "toy"
VHDL implementation in ECE 410. We have also decided to unleash our creativity
and design our own esoteric programming language instead of creating a compiler
for an existing programming language.

With a softcore microprocessor for the hardware aspect, and a compiler for the
software, we have a real full-stack computer engineering project that can be
proud of and can potentially aid in the learning of other computer engineering
students.

## Use Cases

<!-- Use UML diagrams and some annotation to present use cases. See this
\href{https://www.youtube.com/watch?v=zid-MVo7M-E&feature=emb_logo}{tutorial}.
Add descriptive text for each use case. Keep the number of use cases below 15; ≤
10 is best. Figure 1 is an example use case diagram, and Table 1 is a Use Case
description table. If a table is complicated, the use case is probably too
low-level -->

<!-- Insert use case -->

\input{tex/use-case}

<!-- Insert first use case table. -->

\input{tex/uc-001}

\input{tex/uc-002}

\input{tex/uc-003}

\input{tex/uc-004}
