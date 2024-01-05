library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Mock Implementation of memory
-- replace with the real thing when synthesizing to hardware
entity mem is
  port (
    d_i, read_addr_i, write_addr_i : in  std_ulogic_vector (31 downto 0);
    write_en_i                     : in  std_ulogic;
    d_o                            : out std_ulogic_vector (31 downto 0));
end mem;

architecture Behavioral of mem is
  type memory_t is array (5 downto 0) of std_ulogic_vector(31 downto 0);  -- 6 words
  signal memory_s : memory_t := (
    0 => x"000087b7",
    1 => x"12345117",
    2 => x"00a10093",
    3 => x"4027da13",
    4 => x"00f100b3",
    5 => x"402a00b3");
begin
  d_o <= memory_s(to_integer(unsigned(read_addr_i(31 downto 2))));
end Behavioral;
