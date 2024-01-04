library ieee;
use ieee.std_logic_1164.all;

-- Takes a value from memory and outputs its sign-extended value
entity mbr_sx is
  port (
    mbr_i  : in  std_ulogic_vector (31 downto 0);
    size_i : in  std_ulogic_vector (2 downto 0);
    sx_o   : out std_ulogic_vector (31 downto 0));
end mbr_sx;

architecture Behavioral of mbr_sx is
begin
end Behavioral;
