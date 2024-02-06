--! \file alu_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.env.stop;
--! @endcond

--! Test bench for the ALU.
entity alu_tb is
end alu_tb;

architecture test_bench of alu_tb is
  signal a, b, q                             : std_ulogic_vector (31 downto 0) := (others => '0');
  signal op_bits                             : std_ulogic_vector (2 downto 0);
  signal eq_flag, lt_flag, ltu_flag, sub_sra : std_ulogic;

  procedure print_result(lbl : string) is
    use std.textio.all;
    variable my_line : line;
  begin
    wait for 1 ns;
    write(my_line, to_hstring(a));
    write(my_line, ht);
    write(my_line, lbl);
    write(my_line, ht);
    write(my_line, to_hstring(b));
    write(my_line, ht);
    write(my_line, string'(" = "));
    write(my_line, ht);
    write(my_line, to_hstring(q));
    write(my_line, string'(", eq_flag = "));
    write(my_line, eq_flag);
    writeline(output, my_line);
  end procedure print_result;
begin
  alu_inst : entity work.alu(rtl) port map (
    operand_a_i               => a,
    operand_b_i               => b,
    op_bits_i                 => op_bits,
    sub_sra_i                 => sub_sra,
    alu_result_o              => q,
    equal_flag_o              => eq_flag,
    less_than_flag_o          => lt_flag,
    less_than_unsigned_flag_o => ltu_flag);

  process
  begin
    sub_sra <= '0';
    a       <= x"00FF00FF"; b <= x"0000FFFF";

    op_bits <= "111"; print_result("and");
    op_bits <= "110"; print_result("or");
    op_bits <= "100"; print_result("xor");

    op_bits <= "000";
    sub_sra <= '0';

    a <= x"FFFFFFFF"; b <= x"00000001"; print_result("add");

    sub_sra <= '1';

    a <= x"00000000"; b <= x"00000001"; print_result("sub");

    op_bits <= "101";
    sub_sra <= '0';

    a <= x"FFFF0000"; b <= x"00000010"; print_result("srl");

    sub_sra <= '1';

    a <= x"80000000"; b <= x"0000001F"; print_result("sra");

    op_bits <= "010";

    a <= x"00000001"; b <= x"00000002"; print_result("slt");
    a <= x"00000002"; b <= x"00000001"; print_result("slt");

    op_bits <= "011";

    a <= x"00000001"; b <= x"00000002"; print_result("sltu");
    a <= x"80000001"; b <= x"80000002"; print_result("sltu");
    a <= x"80000002"; b <= x"80000001"; print_result("sltu");
    a <= x"40000002"; b <= x"80000001"; print_result("sltu");
    a <= x"FFFFFFFF"; b <= x"FFFFFFFF"; print_result("sltu");
    a <= x"7FFFFFFF"; b <= x"FFFFFFFF"; print_result("sltu");
    stop;

  end process;
end test_bench;
