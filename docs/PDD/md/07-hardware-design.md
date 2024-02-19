\newpage
# High-Level Hardware Design
Outlined in Section \ref{Tab:hardware}, this design presents a typical computer architecture incorporating key components and custom features. The architecture is divided into the following components:

## Core Computational Components
- **Controller**: Acts as the central finite state machine, directing the CPU's components by decoding instructions from the **Instruction Register (IR)**.
- **Program Counter (PC)**: Program counter that holds the address of the current instruction.
- **Instruction Register (IR)**: Stores the current instruction identified by the **PC**.
- **Arithmetic Logic Unit (ALU)**: The computational heart, performing arithmetic and logical operations with data from multiple sources, including the **Register File** and immediate values from instructions.
- **Register File**: A key data source and destination for the ALU, allowing for easy data manipulation and storage.

## Memory Components
  - **ROM (Read-Only Memory)**: Stores firmware which initializes the CPU's software environment at boot time.
  - **RAM (Random-Access Memory)**: The RAM is volatile memory that can be used for temporary data storage.
  - **GPIO Pins**: Input output pins that are mapped to specific addresses and can be read from and written to using load and store instructions.

## Auxiliary Components
- **Random Number Generator (RNG) Seeder**: Uses hardware noise to generate a 32-bit number for random number generation for enhanced security.
