--! \file mem.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.fysh_fyve.mem_t;
--! @endcond

--! Block Memory. \n

entity mem is
  generic (
    --! Address width
    ADDR_W : integer := 15;

    --! Number of words in physical RAM
    NUM_WORDS : integer := (2**ADDR_W);

    --! Data array, can be hardwired
    DATA : mem_t (0 to NUM_WORDS-1) := (others => (31 downto 0 => '0'))
    );

  port(
    d_i               : in  std_ulogic_vector (31 downto 0);
    read_addr_i       : in  std_ulogic_vector (ADDR_W-1 downto 0) := (others => '0');
    write_addr_i      : in  std_ulogic_vector (ADDR_W-1 downto 0) := (others => '0');
    clk_i, write_en_i : in  std_ulogic;
    d_o               : out std_ulogic_vector (31 downto 0));

end mem;

architecture rtl of mem is
  signal RAM : mem_t (0 to NUM_WORDS-1) := DATA;
begin
  process(clk_i)
    use std.textio.all;
    variable l : line;
  begin
    if falling_edge(clk_i) then
      if write_en_i = '1' then
        write(l, string'("writing value "));
        write(l, to_hstring(d_i));
        write(l, string'(" to address 0x"));
        write(l, to_hstring(write_addr_i));
        writeline(output, l);
        RAM(to_integer(unsigned(write_addr_i))) <= d_i;
      end if;
      d_o <= RAM(to_integer(unsigned(read_addr_i)));
    end if;
  end process;
end architecture rtl;
