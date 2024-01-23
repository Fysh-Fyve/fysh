--! \file topmodule_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! Test bench for the top module.
entity topmodule_tb is
end topmodule_tb;

architecture test_bench of topmodule_tb is
  signal clk : std_ulogic;
begin
  topmodule_inst : entity work.topmodule(rtl) port map (clk => clk);
end test_bench;
