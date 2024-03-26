# Betta System Design

(pick one)

The swimming skeleton swam so the betta system could fly. The Betta System
Design is the next step in fysh evolution. We are expanding the language to
include subroutines, improved syntax recognition through a dedicated language
serve(project babel), an interpreter, floating points, and (possibly) strings,
and expanded support for various data types (floats & strings) and operating
systems (Windows, Mac, and Linux). Fysh will also include a contribution file
and an overhauled readme to make this project truly open source. The Fysh-Fyve
Betta System Design will be deployed through the project's public GitHub page.

Hardware will be included in the Betta System Design. The system will include a
fysh swimming animation on an LED matrix display.

## System Architecture

The system architecture largely mirrors that of the swimming skeleton with a few
changes. The largest of which is the mandatory integration of the LLVM backend.
This decision was made after realizing the ease of integration and the
significant benefits it offers in terms of optimization and compatibility across
different hardware platforms.

## Block Diagram

This is just a placeholder

```plaintext
+-----------------+   +-----------------+   +-----------------+
|                 |   |                 |   |                 |
|  Swimming       |==>|  Betta System   |==>|  Fysh-Fyve      |
|  Skeleton       |==>|  Design         |==>|  Betta System   |
|                 |   |                 |   |  Design         |
+-----------------+   +-----------------+   +-----------------+
```

## Changes from swimming skeleton (delete in final version)

Swimming skeleton:

- GPIO construct
- operators
- Loops
- variables
- conditional

New stuff:

- Contribution file (readme)
- Readme 2.0
- Subroutines
- call expressions
- interpreter
- Windows and mac support
- Floating points
- Inclusive strings (unicode)
- Language server (completion, syntax highlighting)
- Esolangs wiki
- Led matrix display & Fysh swimming animation
- Fysh stickers
