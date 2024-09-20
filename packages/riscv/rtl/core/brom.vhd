--! \file brom.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.fysh_fyve.mem_t;
--! @endcond

--! Block Memory. \n

entity brom is
  generic (
    --! Address width
    ADDR_W : integer := 15;

    --! Number of words in physical RAM
    NUM_WORDS : integer := (2**ADDR_W);

    --! Data array, can be hardwired
    DATA : mem_t (0 to NUM_WORDS-1) := (others => (31 downto 0 => '0'))
    );

  port(
    dread_addr_i : in  std_ulogic_vector (ADDR_W-1 downto 0) := (others => '0');
    iread_addr_i : in  std_ulogic_vector (ADDR_W-1 downto 0) := (others => '0');
    clk_i        : in  std_ulogic;
    d_o          : out std_ulogic_vector (31 downto 0);
    i_o          : out std_ulogic_vector (31 downto 0));
end brom;

architecture rtl of brom is
  signal ROM : mem_t (0 to NUM_WORDS-1) := DATA;
begin
  process(clk_i)
    use std.textio.all;
    variable l : line;
  begin
    if falling_edge(clk_i) then
      d_o <= ROM(to_integer(unsigned(dread_addr_i)));
      i_o <= ROM(to_integer(unsigned(iread_addr_i)));
    end if;
  end process;
end architecture rtl;
