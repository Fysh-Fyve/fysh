--! \file imm_sx.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! Immediate Value Sign-extender.\n

--! Takes an immediate value from an instruction and outputs its sign-extended
--! value.
--! TODO: Implement
entity imm_sx is
  port (
    --! The 32-bit instruction.
    instruction_i : in  std_ulogic_vector (31 downto 0);
    --! The immediate value, sign-extended.
    imm_x_o       : out std_ulogic_vector (31 downto 0));
end imm_sx;

architecture Behavioral of imm_sx is
begin
end Behavioral;
