--! \file grilled_fysh_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.env.stop;
--! @endcond

--! Test bench for the Grilled Fysh
entity grilled_fysh_tb is
end grilled_fysh_tb;

architecture test_bench of grilled_fysh_tb is
  signal pins : std_ulogic_vector (7 downto 0);
  signal gf   : std_ulogic_vector (31 downto 0);
  signal clk  : std_ulogic;
begin
  grilled_fysh_inst : entity work.grilled_fysh(rtl) port map (
    clk_i  => clk,
    pins_i => pins,
    gf_o   => gf);

  grilled_fysh_test_cases : process
  begin
    -- TODO: Implement test cases
    stop;
  end process grilled_fysh_test_cases;
end test_bench;
