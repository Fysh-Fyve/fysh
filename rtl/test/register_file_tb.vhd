--! \file register_file.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use std.env.stop;
--! @endcond

--! Test bench for the register file.
entity register_file_tb is
end register_file_tb;

architecture test_bench of register_file_tb is
  signal loop_count    : integer    := 0;
  signal reset, rd_clk : std_ulogic := '0';
  signal clk           : std_ulogic := '0';

  signal rd, rs1, rs2 : std_ulogic_vector (4 downto 0) := (others => '0');

  signal rd_val  : std_ulogic_vector (31 downto 0);
  signal rs1_val : std_ulogic_vector (31 downto 0) := (others => '0');
  signal rs2_val : std_ulogic_vector (31 downto 0) := (others => '0');
begin
  register_file_inst : entity work.register_file(rtl) port map(
    clk_i          => clk,
    rd_write_en_i  => rd_clk,
    reset_i        => reset,
    dest_reg_i     => rd,
    reg_sel_1_i    => rs1,
    reg_sel_2_i    => rs2,
    dest_reg_val_i => rd_val,
    reg_val_1_o    => rs1_val,
    reg_val_2_o    => rs2_val);

  actual_clock : process
  begin
    clk <= '1';
    wait for 10 ns;
    clk <= '0';
    wait for 10 ns;
  end process actual_clock;

  clock : process
  begin
    rd_clk <= '0';
    wait for 20 ns;
    for i in 0 to 31 loop
      rd_clk     <= '1';
      loop_count <= i;
      wait for 20 ns;
      rd_clk     <= '0';
      wait for 20 ns;
    end loop;
    wait;
  end process clock;

  reg_file_testing : process
    use ieee.numeric_std.all;
  begin
    reset  <= '1';
    rd     <= (others => '0');
    rd_val <= (others => '0');
    rs1    <= (others => '0');
    rs2    <= (others => '0');
    wait for 20 ns;

    for i in 0 to 31 loop
      rd <= std_ulogic_vector(to_unsigned(i, 5));
      wait for 20 ns;
      if i > 2 then
        rs1 <= std_ulogic_vector(to_unsigned(i-1, 5));
        rs2 <= std_ulogic_vector(to_unsigned(i-2, 5));
      end if;
      rd_val <= std_ulogic_vector(to_unsigned(i + 1, 32));
      wait for 20 ns;
    end loop;

    stop;
  end process reg_file_testing;

  print_out : process (rd_clk)
    use std.textio.all;
    variable my_line : line;
  begin
    write(my_line, rd_clk);
    write(my_line, ht);
    write(my_line, loop_count);
    write(my_line, ht);
    write(my_line, to_hstring(rs1_val));
    write(my_line, ht);
    write(my_line, to_hstring(rs2_val));
    write(my_line, ht);
    writeline(output, my_line);
  end process print_out;
end test_bench;
