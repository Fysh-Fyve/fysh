--! \file alu_operations_pkg.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! A package containing constants representing the ALU operations.\n
package alu_operations is
  subtype op_t is std_ulogic_vector (2 downto 0);
  constant OP_ADD_SUB            : op_t := "000";  --! A + B or A - B
  constant OP_SHIFT_LEFT         : op_t := "001";  --! A << B(4:0)
  constant OP_LESS_THAN          : op_t := "010";  --! A < B (signed)
  constant OP_LESS_THAN_UNSIGNED : op_t := "011";  --! A < B (unsigned)
  constant OP_XOR                : op_t := "100";  --! A ^ B
  constant OP_SHIFT_RIGHT        : op_t := "101";  --! A >> B(4:0)
  constant OP_OR                 : op_t := "110";  --! A | B
  constant OP_AND                : op_t := "111";  --! A & B
end package alu_operations;
