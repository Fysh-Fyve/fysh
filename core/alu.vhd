library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Before I forget and have to scour Google for this again
-- https://nandland.com/common-vhdl-conversions/

entity alu is
  port (
    a_i, b_i  : in std_ulogic_vector (31 downto 0);
    func_i    : in std_ulogic_vector (2 downto 0);
    sub_sra_i : in std_ulogic;          -- ADD => SUB, SLA => SRA

    q_o               : out std_ulogic_vector (31 downto 0);
    eq_o, lt_o, ltu_o : out std_ulogic);  -- A == B, A < B, A < B (unsigned)
end alu;

architecture Behavioral of alu is
  signal add_s              : signed (31 downto 0);
  signal left_shifted_s     : std_ulogic_vector (31 downto 0);
  signal right_shifted_s    : std_ulogic_vector (31 downto 0);
  signal unsigned_shift_a_s : std_ulogic_vector (31 downto 0);
  signal signed_shift_a_s   : std_ulogic_vector (31 downto 0);
  signal xor_ab_s           : std_ulogic_vector (31 downto 0);

  function less_than_unsigned(
    a : std_ulogic_vector (31 downto 0);
    b : std_ulogic_vector (31 downto 0)) return std_ulogic is
    variable lt : std_ulogic;
  begin
    lt := '1' when to_integer(unsigned(a(30 downto 0))) < to_integer(unsigned(b(30 downto 0))) else '0';
    return (not a(31) and b(31)) or (lt and (a(31) xnor b(31)));
  end function less_than_unsigned;
begin
  with func_i select q_o <=
    a_i and b_i                when "111",
    a_i or b_i                 when "110",
    right_shifted_s            when "101",
    xor_ab_s                   when "100",
    x"0000000" & "000" & ltu_o when "011",
    x"0000000" & "000" & lt_o  when "010",
    left_shifted_s             when "001",
    std_ulogic_vector(add_s)   when "000",
    (others => 'X')            when others;
  xor_ab_s           <= a_i xor b_i;
  add_s              <= (signed(a_i) - signed(b_i)) when sub_sra_i else (signed(a_i) + signed(b_i));
  left_shifted_s     <= std_ulogic_vector(shift_left(unsigned(a_i), to_integer(unsigned(b_i(4 downto 0)))));
  right_shifted_s    <= signed_shift_a_s            when sub_sra_i else unsigned_shift_a_s;
  unsigned_shift_a_s <= std_ulogic_vector(shift_right(unsigned(a_i), to_integer(unsigned(b_i(4 downto 0)))));
  signed_shift_a_s   <= std_ulogic_vector(shift_right(signed(a_i), to_integer(unsigned(b_i(4 downto 0)))));

  eq_o  <= and xor_ab_s;
  lt_o  <= '1' when to_integer(signed(a_i)) < to_integer(signed(b_i)) else '0';
  ltu_o <= less_than_unsigned(a_i, b_i);
end Behavioral;
