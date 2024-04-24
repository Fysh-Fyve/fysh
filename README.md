# Go Fysh 🐟

An implementation of BabelFysh, the interpreter for the
[Fysh Programming Language](https://github.com/Fysh-Fyve/fysh) in Go.

## Why not continue in C++? You already have a working parser.

That's the easiest part to rewrite 😭 It's mostly because packaging a C++ project
is a nightmare. Most likely a skill issue but at this point I just want people
to be able to press the "Play" button on VSCode and run Fysh.

Also, native UTF-8 support makes this super easy

## Installation

Currently, we can only build from source:

```bash
go install github.com/Fysh-Fyve/go-fysh@latest
```
