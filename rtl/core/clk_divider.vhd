--! \file alu.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.fysh_fyve.all;
--! @endcond

entity clk_divider is
  generic (DIV : integer := DIV_NORMAL);
  port (
    clk_i : in  std_ulogic;
    clk_o : out std_ulogic);
end clk_divider;

architecture rtl of clk_divider is
  signal clock_out : std_ulogic := '0';
  signal count     : integer    := 0;
begin
  normal_clock : if DIV = DIV_NORMAL generate
    clk_o <= clk_i;
  end generate normal_clock;

  divided_clock : if (DIV /= DIV_NORMAL) generate
    process (clk_i)
    begin
      if rising_edge(clk_i) then
        count <= count + 1;
        if (count = DIV) then
          clock_out <= not clock_out;
          count     <= 0;
        end if;
      end if;
      clk_o <= clock_out;
    end process;
  end generate divided_clock;
end rtl;
