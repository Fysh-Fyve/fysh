# Betta System Design

The Fysh-Fyve Betta System Design includes features and functionalities of fysh
that are to come after the swimming fysh bones. On top of the many features
existing in the prototype, the Fysh-Fyve Betta System Design adds many
additional features. These include language features such as subroutines
(implemented as submarines) with call expressions, and a language server that
properly recognizes fysh syntax. As well as more wholistic features such as a
possible fysh interpreter which can allow for easier implementation of floating
point numbers and strings, or support for the build on Windows and Mac. These
are all to be deployed the same way which current features are, through the
projects public GitHub page.

## System Architecture

The system architecture did not change much aside from making the LLVM backend
required instead of optional. Our initial assumption was that integrating LLVM
to the project would make it difficult but we had an easy experience with the
library.

## Changes from swimming skeleton

Swimming skeleton: GPIO construct operators Loops variables conditional

New stuff: Contribution file (readme) Readme 2.0 Subroutines call expressions
interpreter Windows and mac support Floating points Inclusive strings (unicode)
Language server (completion, syntax highlighting) Esolangs wiki
