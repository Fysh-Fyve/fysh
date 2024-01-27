--! \file mem.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--! @endcond

--! Block Memory. \n

entity mem is
  generic (
    --! Address width
    ADDR_W    : integer := 15;
    --! Number of words in physical RAM
    NUM_WORDS : integer := (2**ADDR_W);
    --! 0 for byte, 1 for halfword, 2 for word
    OFFSET    : integer := 2;
    --! Top range used for the address
    TOP_RANGE : integer := ADDR_W + OFFSET;
    --! Bottom range used for the address
    BOT_RANGE : integer := OFFSET);
  port(
    d_i, read_addr_i, write_addr_i : in  std_ulogic_vector (31 downto 0);
    clk_i, write_en_i              : in  std_ulogic;
    d_o                            : out std_ulogic_vector (31 downto 0));
end mem;

architecture rtl of mem is
  type ram_t is array (NUM_WORDS-1 downto 0) of std_logic_vector(31 downto 0);
  signal RAM : ram_t := (others => (31 downto 0 => '0'));
begin
  process(clk_i)
  begin
    if rising_edge(clk_i) then
      if write_en_i = '1' then
        RAM(to_integer(unsigned(write_addr_i(TOP_RANGE downto BOT_RANGE)))) <= d_i;
      end if;
      d_o <= RAM(to_integer(unsigned(read_addr_i(TOP_RANGE downto BOT_RANGE))));
    end if;
  end process;
end architecture rtl;
