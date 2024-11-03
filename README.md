# Fysh-Fyve Project

## Structure

All sub-projects are inside the `pkg` directory.

| Project                                                                                       | Description                                                                                            |
| --------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------ |
| [docs-capstone](https://github.com/Fysh-Fyve/fysh/tree/master/pkg/docs-capstone#readme)       | Documentation for [UofA ECE 492 Capstone Project](https://www.capstonedepot.live/post/80)              |
| [fysh-sea](https://github.com/Fysh-Fyve/fysh/tree/master/pkg/fysh-sea#readme)                 | Fysh Compiler (C++ and [LLVM](https://llvm.org/))                                                      |
| [fyshls](https://github.com/Fysh-Fyve/fysh/tree/master/pkg/fyshls#readme)                     | Fysh [Language Server](https://microsoft.github.io/language-server-protocol/)                          |
| [go-fysh](https://github.com/Fysh-Fyve/fysh/tree/master/pkg/go-fysh#readme)                   | Fysh Interpreter based on [Thorsten Ball's Book](https://interpreterbook.com/) (Go)                    |
| [riscv](https://github.com/Fysh-Fyve/fysh/tree/master/pkg/riscv#readme)                       | Hardware Description for Fysh-Fyve [RISC-V](https://riscv.org/) CPU (VHDL)                             |
| [tree-sitter-fysh](https://github.com/Fysh-Fyve/fysh/tree/master/pkg/tree-sitter-fysh#readme) | Fysh [Tree-sitter](https://tree-sitter.github.io/tree-sitter/) Grammar                                 |
| [vscode-fysh](https://github.com/Fysh-Fyve/fysh/tree/master/pkg/vscode-fysh#readme)           | [VSCode Language Support for Fysh](https://marketplace.visualstudio.com/items?itemName=Fysh-Fyve.fysh) |
| [interpreter-web](https://github.com/Fysh-Fyve/fysh/tree/master/pkg/interpreter-web#readme)   | WASM library for the Fysh Web Interpreter                                                              |
| [website](https://github.com/Fysh-Fyve/fysh/tree/master/pkg/website#readme)                   | [Fysh website](https://fysh-fyve.github.io)                                                            |

## Requirements

- `pnpm` - Package manager for JS projects
- `nx` - Monorepo tooling
- `go` - Go toolchain
- `tinygo` - Go toolchain for WASM target
- `wasm-opt` - For optimizing
