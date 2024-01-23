--! \file mem_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--! @endcond

--! Test Bench for the low-level memory component.
entity mem_tb is
end mem_tb;

-- Mock Implementation of memory
-- replace with the real thing when synthesizing to hardware

architecture test_bench of mem_tb is
  signal d_in, read_addr, write_addr : std_ulogic_vector (31 downto 0);
  signal write_en                    : std_ulogic;
  signal d_out                       : std_ulogic_vector (31 downto 0);

  procedure print is
    use std.textio.all;
    variable my_line : line;
  begin
    wait for 1 fs;
    write(my_line, to_hstring(read_addr), left, 8);
    write(my_line, string'(" "));
    write(my_line, to_hstring(d_out), left, 8);
    writeline(output, my_line);
  end procedure print;
begin
  mem_inst : entity work.mem(rtl) port map (
    d_i          => d_in,
    read_addr_i  => read_addr,
    write_addr_i => write_addr,
    write_en_i   => write_en,
    d_o          => d_out);

  print_mem : process
  begin
    read_addr <= (others => '0');
    print;
    for i in 0 to 4 loop
      read_addr <= std_ulogic_vector (signed(read_addr) + 4);
      print;
    end loop;
    wait;
  end process print_mem;
end test_bench;
