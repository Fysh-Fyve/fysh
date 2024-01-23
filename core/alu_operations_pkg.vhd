--! \file alu_operations_pkg.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! A package containing constants representing the ALU operations.\n
package alu_operations is
  subtype op is std_ulogic_vector (2 downto 0);
  --! A + B or A - B
  constant OP_ADD_SUB            : op := "000";
  --! A << B(4:0)
  constant OP_SHIFT_LEFT         : op := "001";
  --! A < B
  constant OP_LESS_THAN          : op := "010";
  --! A < B (unsigned)
  constant OP_LESS_THAN_UNSIGNED : op := "011";
  --! A ^ B
  constant OP_XOR                : op := "100";
  --! A >> B(4:0)
  constant OP_SHIFT_RIGHT        : op := "101";
  --! A | B
  constant OP_OR                 : op := "110";
  --! A & B
  constant OP_AND                : op := "111";
end package alu_operations;
