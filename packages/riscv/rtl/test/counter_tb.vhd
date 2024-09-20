--! \file counter_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.env.stop;
--! @endcond

--! Test bench for the Counter.
entity counter_tb is
end counter_tb;

architecture test_bench of counter_tb is
  signal kent : std_ulogic_vector (31 downto 0) := (others => '0');
  signal clk  : std_ulogic;

begin
  counter_inst : entity work.counter(rtl)
    generic map (START => 2**30 -1)
    port map (clk_i    => clk, count_o => kent);

  process
    use std.textio.all;
    variable l : line;
  begin
    for j in 0 to 4 loop
      clk <= '1';
      write(l, string'("kent: "));
      write(l, to_hstring(kent));
      writeline(output, l);
      wait for 10 ns;
      clk <= '0';
      wait for 10 ns;
    end loop;
    stop;
  end process;
end test_bench;
