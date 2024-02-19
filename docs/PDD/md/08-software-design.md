# High-Level Software/Firmware Design

This document outlines the design of the Fysh programming language compiler and
its execution on custom hardware. As shown in Section \ref{Tab:software}, the Fysh compiler translates Fysh code into
executable machine code using C++ for backend processing. This process is
divided into three primary stages: Front End, Middle End (optional), and Back
End.

## Compiler Architecture

### Front End

- **Lexer**: The lexer takes in Fysh code as input and tokenizes it, producing a
  sequence of tokens that the parser can interpret.
- **Parser**: The parser takes a sequence of tokens from the lexer and produces
  an Abstract Syntax Tree (AST) while ensuring the syntax is correct.
- **Semantic Analyzer**: The Semantic Analyzer traverses the AST to verify
  semantic consistency, ensuring the code follows the rules of the language.

### Middle End (Optional)

- **Intermediate Representation (IR)**: This stage involves translating the AST
  into a platform-independent, intermediate representation. This step is crucial
  for optimization.
- **Optimization Passes**: The IR undergoes various optimization passes to
  improve efficiency and performance. These optimizations may include code
  simplification and dead code elimination.

### Back End

- **Code Generation**: The final stage converts the optimized IR into machine
  code specific to the target hardware, making the program executable.

## Introduction to the Fysh Programming Language

_Fysh is designed to be a fun programming language that is initially
intimidating but ultimately rewarding. It is a statically-typed, compiled
language with a focus on having fun while programming. The full language
specification can be found on
**[Github](https://github.com/Fysh-Fyve/fysh/blob/main/README.md)**._

\
**Practical Example: Factorial Calculation in Fysh**

```fysh
><number>    = ><})}>   ><//> Initialize number to 5
><factorial> = ><))}>   ><//> Initialize factorial to 1

><//> While loop: continue while number > 1
><(((@> [ ><number>  o~  ><))}> ]
><>
    ><//> Calculate factorial: factorial = factorial * number
    ><factorial> = ><factorial> <3 ><number> ~

    ><//> Decrement number by 1
    <number><< ~
<><
```

**Explanation:**

- `><number> = ><})}>` initializes number with the binary value `101` (5 in
  decimal). (`} = 1`, `) = 0`)

- `><factorial> = ><))}>` initializes factorial with the binary value `001` (1
  in decimal). (`} = 1`, `) = 0`)

- `><(((@> [><number> o~ ><))}>]` is a while loop that continues while the
  number is greater than 1. ( `><(((@>` is the while loop operator, `o~` is the
  greater than operator)

- Inside the while loop, `><factorial> = ><factorial> <3 ><number> ~` calculates
  the factorial by multiplying the current factorial with the number and storing
  the result back in the factorial. (`<3` is the multiplication operator)

- `<number><< ~` decrements the number by 1.

- The program ends when the number is no longer greater than 1.

- The final result is stored in the `factorial` variable.

This example demonstrates the unique syntax and features of Fysh, which is
designed to be fun and challenging to use.
