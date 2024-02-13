# High-Level Hardware Design

The hardware design as described in Section \ref{Tab:hardware} follows a typical
computer architecture with registers, program counter (PC), arithmetic logic
unit (ALU), controller, and memory.

The **controller** is a finite state machine that drives all the other
components of the CPU. The controller decides which components are selected on
the datapath by decoding the instructions from the **instruction register**. The
instruction register holds the instruction stored in the address that is held by
the **PC**.

The **ALU** performs all the computations using values from various sources. The
**register file** is the most common data source and destination of operations
but the PC and immediate values from the instruction can also be used as a
source.

The **RNG seeder** is a hardware component that uses hardware noise to generate
a 32-bit number for random number generation. This makes it more difficult to
predict the randomly-generated values unlike using other physical properties
like the current time or the MAC address of a machine.

The memory address space of the CPU is comprised of the **ROM**, the **RAM**,
and the **GPIO pins**. The ROM contains the firmware that is pre-programmed into
the CPU before boot time. The RAM is volatile memory that can be used for
temporary data storage. The GPIO pins are mapped to specific addresses and are
read from and written to using load and store instructions, respectively.
