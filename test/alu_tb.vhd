library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity alu_tb is
end alu_tb;

architecture Behavioral of alu_tb is
  signal a, b, q              : std_ulogic_vector (31 downto 0) := (others => '0');
  signal func                 : std_ulogic_vector (2 downto 0);
  signal eq, lt, ltu, sub_sra : std_ulogic;
  component alu is port (
    a, b        : in  std_ulogic_vector (31 downto 0);
    func        : in  std_ulogic_vector (2 downto 0);
    sub_sra     : in  std_ulogic;       -- ADD => SUB, SLA => SRA
    q           : out std_ulogic_vector (31 downto 0);
    eq, lt, ltu : out std_ulogic);      -- A == B, A < B, A < B (unsigned)
  end component;

  procedure print_q(lbl : string) is
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
    writeline(output, my_line);
  end procedure print_q;
begin
  alu_test : component alu port map (
    a       => a,
    b       => b,
    func    => func,
    sub_sra => sub_sra,
    q       => q,
    eq      => eq,
    lt      => lt,
    ltu     => ltu);

  process
  begin
    sub_sra <= '0';
    a       <= x"00FF00FF"; b <= x"0000FFFF";

    func <= "111"; print_q("and");
    func <= "110"; print_q("or");
    func <= "100"; print_q("xor");

    func    <= "000";
    sub_sra <= '0';

    a <= x"FFFFFFFF"; b <= x"00000001"; print_q("add");

    sub_sra <= '1';

    a <= x"00000000"; b <= x"00000001"; print_q("sub");

    func    <= "101";
    sub_sra <= '0';

    a <= x"FFFF0000"; b <= x"00000010"; print_q("srl");

    sub_sra <= '1';

    a <= x"80000000"; b <= x"0000001F"; print_q("sra");

    func <= "010";

    a <= x"00000001"; b <= x"00000002"; print_q("slt");
    a <= x"00000002"; b <= x"00000001"; print_q("slt");

    func <= "011";

    a <= x"00000001"; b <= x"00000002"; print_q("sltu");
    a <= x"80000001"; b <= x"80000002"; print_q("sltu");
    a <= x"80000002"; b <= x"80000001"; print_q("sltu");
    a <= x"40000002"; b <= x"80000001"; print_q("sltu");
    a <= x"FFFFFFFF"; b <= x"FFFFFFFF"; print_q("sltu");
    a <= x"7FFFFFFF"; b <= x"FFFFFFFF"; print_q("sltu");
    wait;
  end process;
end Behavioral;
