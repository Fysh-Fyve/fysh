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
  signal pins : std_ulogic_vector (7 downto 0)  := (others => '0');
  signal gf   : std_ulogic_vector (31 downto 0) := (others => '0');
  signal clk  : std_ulogic                      := '0';


  type data_t is array (natural range <>) of std_ulogic_vector(7 downto 0);
  -- Add whatever random data you want here and check the bit pattern of the
  -- grilled fysh
  constant data : data_t := (
    x"DE",
    x"AD",
    x"BE",
    x"EF",
    x"F1",
    x"54",
    x"C0",
    x"DE",
    x"C0",
    x"FF",
    x"EE");
begin
  grilled_fysh_inst : entity work.grilled_fysh(rtl) port map (
    clk_i  => clk,
    pins_i => pins,
    gf_o   => gf);

  grilled_fysh_test_cases : process
  begin
    clk <= '0';
    wait for 10 ns;
    for i in 0 to 50 loop
      clk <= '1';
      wait for 10 ns;

      pins <= data(i mod data'length);
      report ht & to_hstring(gf);

      clk <= '0';
      wait for 10 ns;
    end loop;
    stop;
  end process grilled_fysh_test_cases;
end test_bench;
