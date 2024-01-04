library ieee;
use ieee.std_logic_1164.all;

entity mem is
  port (
  d_i, read_addr_i, write_addr_i : in  std_ulogic_vector (31 downto 0);
  write_en_i                     : in  std_ulogic;
  d_o                            : out std_ulogic_vector (31 downto 0));
end mem;

architecture Behavioral of mem is
begin
end Behavioral;
