--! \file alu_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--! @endcond

--! Test bench for the ALU.
entity alu_tb is
end alu_tb;

architecture Behavioral of alu_tb is
  signal a, b, q                            : std_ulogic_vector (31 downto 0) := (others => '0');
  signal op_bits                            : std_ulogic_vector (2 downto 0);
  signal eq, lt, ltu, add_shift_modify_flag : std_ulogic;
  component alu is port (
    operand_a_i, operand_b_i                                  : in  std_ulogic_vector (31 downto 0);
    op_bits_i                                                 : in  std_ulogic_vector (2 downto 0);
    add_shift_modify_flag_i                                   : in  std_ulogic;
    alu_result_o                                              : out std_ulogic_vector (31 downto 0);
    equal_flag_o, less_than_flag_o, less_than_unsigned_flag_o : out std_ulogic);
  end component;

  procedure print_result(lbl : string) is
    use std.textio.all;
    variable my_line : line;
  begin
    wait for 1 fs;
    write(my_line, to_hstring(a), left, 8);
    write(my_line, string'(" "));
    write(my_line, lbl, left, 5);
    write(my_line, to_hstring(b), left, 8);
    write(my_line, string'(" = "));
    write(my_line, to_hstring(q), left, 8);
    write(my_line, string'(", eq = "));
    write(my_line, eq, left, 8);
    writeline(output, my_line);
  end procedure print_result;
begin
  alu_inst : component alu port map (
    operand_a_i               => a,
    operand_b_i               => b,
    op_bits_i                 => op_bits,
    add_shift_modify_flag_i   => add_shift_modify_flag,
    alu_result_o              => q,
    equal_flag_o              => eq,
    less_than_flag_o          => lt,
    less_than_unsigned_flag_o => ltu);

  process
  begin
    add_shift_modify_flag <= '0';
    a                     <= x"00FF00FF"; b <= x"0000FFFF";

    op_bits <= "111"; print_result("and");
    op_bits <= "110"; print_result("or");
    op_bits <= "100"; print_result("xor");

    op_bits               <= "000";
    add_shift_modify_flag <= '0';

    a <= x"FFFFFFFF"; b <= x"00000001"; print_result("add");

    add_shift_modify_flag <= '1';

    a <= x"00000000"; b <= x"00000001"; print_result("sub");

    op_bits               <= "101";
    add_shift_modify_flag <= '0';

    a <= x"FFFF0000"; b <= x"00000010"; print_result("srl");

    add_shift_modify_flag <= '1';

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
    wait;
  end process;
end Behavioral;
