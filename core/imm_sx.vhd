library ieee;
use ieee.std_logic_1164.all;

-- Takes an immediate value from an instruction and outputs its sign-extended value
entity imm_sx is
  port (
    insn_i  : in  std_ulogic_vector (31 downto 0);
    imm_x_o : out std_ulogic_vector (31 downto 0));
end imm_sx;

architecture Behavioral of imm_sx is
begin
end Behavioral;
