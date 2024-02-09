# High-Level Software/Firmware Design

<!-- For each software/firmware component in the architecture, describe its
implementation and how it is related to other components. 1 page max -->

The most abstract explanation of the software aspect of the project would be
that a fysh program is compiled by the custom fysh compiler and executed on our
hardware. More in depth, the compiler consists of multiple components which
break down the fysh program so that it can be understood and executed using C++.
The first of these components is the lexer, which takes in fysh code as input
and turns it into a series of tokens, i.e tokenizes. Following the lexer is the
parser, which takes a sequence of tokens from the lexer and produces an AST of
the program while verifying the syntax.
