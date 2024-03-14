--! \file gpio_pins_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.env.stop;
--! @endcond

--! Test bench for the GPIO pins
entity gpio_pins_tb is
end gpio_pins_tb;

architecture test_bench of gpio_pins_tb is
  signal clk             : std_ulogic;
  signal gp_io           : std_ulogic_vector (31 downto 0) := (others => '0');
  signal write_en_i      : std_ulogic;
  signal mode_write_en_i : std_ulogic;
  signal pin_mode_i      : std_ulogic_vector (31 downto 0);
  signal pin_write_i     : std_ulogic_vector (31 downto 0);
  signal pin_read_o      : std_ulogic_vector (31 downto 0);
  signal mode_o          : std_ulogic_vector (31 downto 0);
begin
  gpio_inst : entity work.gpio_pins(rtl)
    port map (
      clk_i           => clk,
      gp_io           => gp_io,
      write_en_i      => write_en_i,
      mode_write_en_i => mode_write_en_i,
      pin_mode_i      => pin_mode_i,
      pin_write_i     => pin_write_i,
      pin_read_o      => pin_read_o,
      mode_o          => mode_o);

  clock : process
  begin
    clk <= '0';
    wait for 10 ns;
    clk <= '1';
    wait for 10 ns;
  end process clock;

  gpio_pins_test_cases : process
  begin
    pin_mode_i      <= x"F0F0F0F0";
    mode_write_en_i <= '1';
    wait for 40 ns;
    pin_write_i     <= x"FFFFFFFF";
    write_en_i      <= '1';
    wait for 40 ns;
    report to_hstring(pin_read_o);
    pin_write_i     <= x"00000000";
    wait for 40 ns;
    report to_hstring(pin_read_o);
    stop;
  end process gpio_pins_test_cases;
end test_bench;
