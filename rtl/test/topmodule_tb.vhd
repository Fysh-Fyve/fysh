--! \file topmodule_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use std.env.stop;
use work.fysh_fyve.all;
--! @endcond

--! Test bench for the top module.
entity topmodule_tb is
  -- generic (VERBOSE : boolean := false);
  generic (VERBOSE : boolean := false; GPIO_VERBOSE : boolean := true);
end topmodule_tb;

architecture test_bench of topmodule_tb is
  signal clk   : std_ulogic                      := '0';
  signal gpio  : std_ulogic_vector (31 downto 0) := (others => '0');
  signal reset : std_ulogic                      := '1';
  signal done  : std_ulogic                      := '0';
  signal adc   : std_ulogic_vector(7 downto 0);

  type data_t is array (natural range <>) of std_ulogic_vector(7 downto 0);
  -- Add whatever random data you want here and check the bit pattern of the
  -- grilled fysh
  constant data : data_t := (
    x"DE", x"AD", x"BE", x"EF",
    x"F1", x"54",
    x"0F", x"F1", x"CE",
    x"00", x"BA", x"B1", x"0C",
    x"1B", x"AD", x"B0", x"02"
    );
  signal idx : integer := 0;
begin
  drive_clock : process
  begin
    clk <= not clk;
    wait for 10 ns;
  end process drive_clock;

  adc_data : process(clk)
  begin
    if rising_edge(clk) then
      adc <= data(idx);
      idx <= (idx + 1) mod data'length;
    end if;
  end process adc_data;

  topmodule_inst : entity work.topmodule(rtl)
    generic map (
      VERBOSE      => VERBOSE,
      GPIO_VERBOSE => GPIO_VERBOSE,
      DIV_CLK      => DIV_NORMAL)
    port map (
      clk   => clk,
      gpio  => gpio,
      done  => done,
      reset => reset,
      adc   => adc);
  process
  begin
    wait for 10 ns;
    reset <= '1';
    wait for 10 ns;
    reset <= '0';
    wait for 10 ns;
    reset <= '1';
    wait for 10 ns;
    reset <= '0';
    wait until rising_edge(done);
    wait for 100 ns;
    stop;
  end process;
end test_bench;
