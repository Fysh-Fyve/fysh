--! \file counter.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.numeric_std.all;
use ieee.std_logic_1164.all;
--! @endcond

--! Counts.\n

entity counter is
  generic (START : integer := 0);
  port (
    clk_i   : in  std_ulogic;
    count_o : out std_ulogic_vector (31 downto 0));
end counter;

architecture rtl of counter is
  signal c : integer := START;
begin
  process(clk_i)
  begin
    if rising_edge(clk_i) then
      if c = 2**30-1 then
        c <= 0;
      else
        c <= to_integer(to_unsigned(c + 1, 31));
      end if;
    end if;
  end process;

  count_o <= '0' & std_ulogic_vector(to_unsigned(c, 31));
end rtl;
