--! \file mem_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.env.stop;
use work.rom.rom_arr;
use work.fysh_fyve.ROM_ADDR_W;
--! @endcond

--! Test Bench for the physical address mapping.
entity phy_map_tb is
end phy_map_tb;

architecture test_bench of phy_map_tb is
  signal clk      : std_ulogic := '0';  --! Clock signal
  signal write_en : std_ulogic;         --! Write enable

  signal iraddr : std_ulogic_vector (31 downto 0);  --! Instruction Read Address
  signal draddr : std_ulogic_vector (31 downto 0);  --! Data Read Address
  signal waddr  : std_ulogic_vector (31 downto 0);  --! Write Address
  signal d_i    : std_ulogic_vector (31 downto 0);  --! Data Input
  signal d_o    : std_ulogic_vector (31 downto 0);  --! Data Output
  signal i_o    : std_ulogic_vector (31 downto 0);  --! Instruction Output
  signal gpio   : std_ulogic_vector (31 downto 0);  --! GPIO Pins

  procedure print is
    use std.textio.all;
    variable my_line : line;
  begin
    write(my_line, to_hstring(draddr));
    write(my_line, ht);
    write(my_line, to_hstring(d_o));
    writeline(output, my_line);
  end procedure print;
begin
  mem_inst : entity work.phy_map(rtl)
    generic map(VERBOSE => true)
    port map (
      clk_i      => clk,
      draddr_i   => draddr,
      iraddr_i   => iraddr,
      waddr_i    => waddr,
      write_en_i => write_en,
      d_i        => d_i,
      d_o        => d_o,
      i_o        => i_o,
      gpio       => gpio);

  draddr <= std_ulogic_vector (signed(waddr) - 64);

  clock : process
  begin
    clk <= not clk;
    wait for 10 ns;
  end process clock;

  woop : process
  begin
    wait until rising_edge(clk);
    write_en <= '1';
    waddr    <= (others => '0');
    d_i      <= (others => '1');
    for i in 0 to 2048 loop
      wait until rising_edge(clk);
      print;
      waddr <= std_ulogic_vector (signed(waddr) + 64);
      wait until falling_edge(clk);
    end loop;
    stop;
  end process woop;
end test_bench;
