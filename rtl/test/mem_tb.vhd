--! \file mem_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.env.stop;
use work.rom.rom_arr;
--! @endcond

--! Test Bench for the low-level memory component.
entity mem_tb is
end mem_tb;

architecture test_bench of mem_tb is
  signal d_in, read_addr, write_addr : std_ulogic_vector (31 downto 0);
  signal clk, write_en               : std_ulogic := '0';
  signal d_out                       : std_ulogic_vector (31 downto 0);

  procedure print is
    use std.textio.all;
    variable my_line : line;
  begin
    wait for 1 ns;
    write(my_line, to_hstring(read_addr));
    write(my_line, ht);
    write(my_line, to_hstring(d_out));
    writeline(output, my_line);
  end procedure print;
begin
  mem_inst : entity work.mem(rtl)
    generic map (DATA => rom_arr)
    port map (
      clk_i        => clk,
      d_i          => d_in,
      read_addr_i  => read_addr(16 downto 2),
      write_addr_i => write_addr(16 downto 2),
      write_en_i   => write_en,
      d_o          => d_out);

  write_addr <= read_addr;

  clock : process
  begin
    clk <= not clk;
    wait for 1 ns;
  end process clock;

  print_mem : process
  begin
    read_addr <= (others => '0');
    print;
    for i in 0 to 4 loop
      read_addr <= std_ulogic_vector (signed(read_addr) + 4);
      print;
    end loop;
    stop;
  end process print_mem;
end test_bench;
