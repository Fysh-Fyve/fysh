To create a syntax guide for your custom language, "Fysh," in Markdown, you'll want to organize the rules and examples you've provided into a structured format that's easy to read and understand. Below is an example of how you might structure this guide, incorporating the syntax and rules of Fysh:

---

# Fysh Language Syntax Guide

Fysh is a whimsical, fish-themed programming language that offers a unique approach to coding through aquatic metaphors and binary scales. This guide provides an overview of the syntax and features of Fysh.

## Basic Syntax

### Variables
Declare a variable (e.g., Steven) using `><variableName>`.
```fysh
><steven>
```

### Termination
Every Fysh code block must be terminated with a `~`.
```fysh
><steven> ~
```

### Binary Scales
Binary values are represented with `}` for 1 and `)` for 0. Assign binary values using `=` or `≈`.
```fysh
><steven> = ><})}> ~
><steven> ≈ ><}({> ~
```

### Optional Feature
You can optionally add features to variables, like giving Steven sight with `°` or `o`.
```fysh
><steven> ≈ ><{({°> ~
><steven> = ><{({o> ~
```

## Operators

### Arithmetic Operations
Fysh supports addition, subtraction, multiplication, and division through creative symbols.
- **Addition:** Sum of individual values in a school of fysh. (e.g., `><{((°> + ><(({°> ~`)
- **Subtraction:** Represented by fysh swimming in opposite directions. (e.g., `><{{{°> <°)})>< ~`)
- **Multiplication:** Represented by a heart symbol `♡` or a lesser form of love `<3`.
- **Division:** Symbolized by a heartbreak `💔` or `</3`.

### Increment and Decrement
Grow an extra tail to increment and swim in the opposite direction to decrement.
```fysh
>><steven> ~
<steven><< ~
```

### Error Handling
Use `><!@#$>` and `<!@#$><` to throw an error.
```fysh
><!@#$>
    What The Fysh?!
<!@#$><
```

### Equality and Inequality
Check for equality with `≈≈` or `==`, and inequality with `~≈` or `~=`.
```fysh
><steven> ≈≈ ><theFysh> ~
><steven> ~= ><theFysh> ~
```

### Comparison Operators
Use variations of `o~` and `~o` for greater than, less than. And `o~≈` and `~o≈` for greater than or equal to, less than or equal to.
```fysh
><steven> o~ ><sixFins> ~
><steven> o~≈ ><sixFins> ~
><steven> ~o ><sixFins> ~
><steven> ~o= ><sixFins> ~
```

### Logical Operators
Combine conditions with `&&` for AND, `||` for OR, and negate with `!!`.
```fysh
><steven> && ><theTruth> ~
><steven> || ><theTruth> ~
!! ><steven> ~
```

### Bitwise Operations
Fysh supports `AND`, `OR`, `XOR`, `NOT`, and shift operations.
```fysh
><steven> &  ><{((°> ~
><steven> |  ><{((°> ~
><steven> ^  ><{((°> ~
! ><steven>
><steven> << ><{((°> ~
><steven> >> ><{((°> ~
```

## Control Structures

### Loops
Use `><(((@>` for while loops.
```fysh
><(((@> [ ><steven> o~ ><{((°> ]
><>
    <steven><< ~
<><
```

### Conditional Statements
`><(((^>` for if, `><(((*> ><(((^>` for else if, and `><(((*>` for else.
```fysh
><(((^> [ ><steven> o~ ><{((°> ]
><>
    <steven><< ~
<><
```

## Comments
Single-line comments with `><//>` and multi-line with `></*>` and `<*/><`.
```fysh
><//> This is a comment.
></*>
Multi-line comment
<*/><
```

## Arrays
Define arrays with `[ ]` and separate elements with `-`. Access elements using `><varName>[index]`.
```fysh
><steven> ≈ [><({(°> - ><({(°>] ~
><steven>[><(({°>]
```

## Factorial Example
A complete example demonstrating the factorial calculation.
```fysh
><//> Factorial calculation example
><number>    ≈ ><{({°>   ><//> b101 = 5
><factorial> ≈ ><(({°>   ><//> b001 = 1

><(((@> [><number> o~ ><(({°>]
><>
    ><//> factorial = factorial * number
    ><factorial> ≈ ><factorial> ♡ ><number> ~ 
    
    ><//> number -= 1
    <number><< ~ 
<><
```