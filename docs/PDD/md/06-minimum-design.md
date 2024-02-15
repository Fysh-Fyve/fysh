# Minimum Design

In this section a minimum design, the "walking skeleton" is described. The
purpose is to define the functionality to be implemented in the first
development iteration. The outcome is reported to the client providing an
opportunity for early feedback.

### Fysh-Fyve (RISC-V Processor)

\input{tex/min-chyp}

Hardware RNG and GPIO. The purpose is to demonstrate that the processor can be
synthesized and that the basic peripherals can be implemented and tested.

### Fysh (Esoteric Language Compiler)

A compiler that can handle basic arithmetic, bit manipulation, memory addressing
and loops. The purpose is to demonstrate that the compiler can generate RISC-V
assembly code and that the code can be executed on the Fysh-Fyve processor.

\input{tex/min-fysh}
