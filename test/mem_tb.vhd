library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity mem_tb is
end mem_tb;

-- Mock Implementation of memory
-- replace with the real thing when synthesizing to hardware

architecture Behavioral of mem_tb is
  component mem is port (
    d_i, read_addr_i, write_addr_i : in  std_ulogic_vector (31 downto 0);
    write_en_i                     : in  std_ulogic;
    d_o                            : out std_ulogic_vector (31 downto 0));
  end component;
  signal d_in, read_addr_s, write_addr_s : std_ulogic_vector (31 downto 0);
  signal write_en_s                      : std_ulogic;
  signal d_out                           : std_ulogic_vector (31 downto 0);

  procedure print is
    use std.textio.all;
    variable my_line : line;
  begin
    wait for 1 fs;
    write(my_line, to_hstring(read_addr_s), left, 8);
    write(my_line, string'(" "));
    write(my_line, to_hstring(d_out), left, 8);
    writeline(output, my_line);
  end procedure print;
begin
  mem_u : component mem port map (
    d_i          => d_in,
    read_addr_i  => read_addr_s,
    write_addr_i => write_addr_s,
    write_en_i   => write_en_s,
    d_o          => d_out);

  print_p : process
  begin
    read_addr_s <= (others => '0');
    print;
    for i in 0 to 4 loop
      read_addr_s <= std_ulogic_vector (signed(read_addr_s) + 4);
      print;
    end loop;
    wait;
  end process print_p;
end Behavioral;
