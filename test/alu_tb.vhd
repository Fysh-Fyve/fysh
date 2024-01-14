--! \file alu_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--! @endcond

entity alu_tb is
end alu_tb;

architecture Behavioral of alu_tb is
  signal a, b, q              : std_ulogic_vector (31 downto 0) := (others => '0');
  signal func                 : std_ulogic_vector (2 downto 0);
  signal eq, lt, ltu, sub_sra : std_ulogic;
  component alu is port (
    a_i, b_i          : in  std_ulogic_vector (31 downto 0);
    func_i            : in  std_ulogic_vector (2 downto 0);
    sub_sra_i         : in  std_ulogic;
    q_o               : out std_ulogic_vector (31 downto 0);
    eq_o, lt_o, ltu_o : out std_ulogic);
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
    a_i       => a,
    b_i       => b,
    func_i    => func,
    sub_sra_i => sub_sra,
    q_o       => q,
    eq_o      => eq,
    lt_o      => lt,
    ltu_o     => ltu);

  process
  begin
    sub_sra <= '0';
    a       <= x"00FF00FF"; b <= x"0000FFFF";

    func <= "111"; print_result("and");
    func <= "110"; print_result("or");
    func <= "100"; print_result("xor");

    func    <= "000";
    sub_sra <= '0';

    a <= x"FFFFFFFF"; b <= x"00000001"; print_result("add");

    sub_sra <= '1';

    a <= x"00000000"; b <= x"00000001"; print_result("sub");

    func    <= "101";
    sub_sra <= '0';

    a <= x"FFFF0000"; b <= x"00000010"; print_result("srl");

    sub_sra <= '1';

    a <= x"80000000"; b <= x"0000001F"; print_result("sra");

    func <= "010";

    a <= x"00000001"; b <= x"00000002"; print_result("slt");
    a <= x"00000002"; b <= x"00000001"; print_result("slt");

    func <= "011";

    a <= x"00000001"; b <= x"00000002"; print_result("sltu");
    a <= x"80000001"; b <= x"80000002"; print_result("sltu");
    a <= x"80000002"; b <= x"80000001"; print_result("sltu");
    a <= x"40000002"; b <= x"80000001"; print_result("sltu");
    a <= x"FFFFFFFF"; b <= x"FFFFFFFF"; print_result("sltu");
    a <= x"7FFFFFFF"; b <= x"FFFFFFFF"; print_result("sltu");
    wait;
  end process;
end Behavioral;
