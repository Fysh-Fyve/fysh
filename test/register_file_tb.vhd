--! \file register_file.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! Test bench for the register file.
entity register_file_tb is
end register_file_tb;

architecture test_bench of register_file_tb is
  signal loop_count    : integer    := 0;
  signal reset, rd_clk : std_ulogic := '0';

  signal rd, rs1, rs2 : std_ulogic_vector (4 downto 0) := (others => '0');

  signal rd_val           : std_ulogic_vector (31 downto 0);
  signal rs1_val, rs2_val : std_ulogic_vector (31 downto 0) := (others => '0');
begin
  register_file_inst : entity work.register_file(rtl) port map(
    rd_clk_i       => rd_clk,
    reset_i        => reset,
    dest_reg_i     => rd,
    reg_sel_1_i    => rs1,
    reg_sel_2_i    => rs2,
    dest_reg_val_i => rd_val,
    reg_val_1_o    => rs1_val,
    reg_val_2_o    => rs2_val);

  clock : process
  begin
    rd_clk <= '0';
    wait for 1 ns;
    for i in 0 to 31 loop
      rd_clk     <= '1';
      loop_count <= i;
      wait for 5 ns;
      rd_clk     <= '0';
      wait for 5 ns;
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
    wait for 1 ns;

    for i in 0 to 31 loop
      rd <= std_ulogic_vector(to_unsigned(i, 5));
      wait for 5 ns;
      if i > 2 then
        rs1 <= std_ulogic_vector(to_unsigned(i-1, 5));
        rs2 <= std_ulogic_vector(to_unsigned(i-2, 5));
      end if;
      rd_val <= std_ulogic_vector(to_unsigned(i + 1, 32));
      wait for 5 ns;
    end loop;

    wait;
  end process reg_file_testing;

  --! This only works on GHDL unfortunately.
  --! Well, you can directly inspect the waveforms on Vivado.

-- print_out : process (rd_clk)
--   use std.textio.all;
--   variable my_line : line;
-- begin
--   write(my_line, rd_clk, left, 5);
--   write(my_line, loop_count, left, 5);
--   write(my_line, to_hstring(rs1_val), left, 10);
--   write(my_line, to_hstring(rs2_val), left, 10);
--   writeline(output, my_line);
-- end process print_out;
end test_bench;
