--! \file topmodule_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use std.env.stop;
--! @endcond

--! Test bench for the top module.
entity topmodule_tb is
end topmodule_tb;

architecture test_bench of topmodule_tb is
  signal clk  : std_ulogic;
  signal gpio : std_ulogic_vector (31 downto 0);
begin
  topmodule_inst : entity work.topmodule(rtl) port map (
    clk  => clk,
    gpio => gpio);
  process
  begin
    wait for 1 ns;
    stop;
  end process;
end test_bench;
