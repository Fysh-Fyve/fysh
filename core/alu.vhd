library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Before I forget and have to scour Google for this again
-- https://nandland.com/common-vhdl-conversions/

entity alu is
  port (
    a, b    : in std_ulogic_vector (31 downto 0);
    func    : in std_ulogic_vector (2 downto 0);
    sub_sra : in std_ulogic;            -- ADD => SUB, SLA => SRA

    q           : out std_ulogic_vector (31 downto 0);
    eq, lt, ltu : out std_ulogic);      -- A == B, A < B, A < B (unsigned)
end alu;

architecture Behavioral of alu is
  signal add              : signed (31 downto 0);
  signal left_shifted     : std_ulogic_vector (31 downto 0);
  signal right_shifted    : std_ulogic_vector (31 downto 0);
  signal unsigned_shift_a : std_ulogic_vector (31 downto 0);
  signal signed_shift_a   : std_ulogic_vector (31 downto 0);
  signal xor_ab           : std_ulogic_vector (31 downto 0);

  function less_than_u(
    a : std_ulogic_vector (31 downto 0);
    b : std_ulogic_vector (31 downto 0)) return std_ulogic is
    variable lt : std_ulogic;
  begin
    lt := '1' when to_integer(unsigned(a(30 downto 0))) < to_integer(unsigned(b(30 downto 0))) else '0';
    return (not a(31) and b(31)) or (lt and (a(31) xnor b(31)));
  end function less_than_u;
begin
  with func select q <=
    a and b                  when "111",
    a or b                   when "110",
    right_shifted            when "101",
    xor_ab                   when "100",
    x"0000000" & "000" & ltu when "011",
    x"0000000" & "000" & lt  when "010",
    left_shifted             when "001",
    std_ulogic_vector(add)   when "000",
    (others => 'X')          when others;
  xor_ab           <= a xor b;
  add              <= (signed(a) - signed(b)) when sub_sra else (signed(a) + signed(b));
  left_shifted     <= std_ulogic_vector(shift_left(unsigned(a), to_integer(unsigned(b(4 downto 0)))));
  right_shifted    <= signed_shift_a          when sub_sra else unsigned_shift_a;
  unsigned_shift_a <= std_ulogic_vector(shift_right(unsigned(a), to_integer(unsigned(b(4 downto 0)))));
  signed_shift_a   <= std_ulogic_vector(shift_right(signed(a), to_integer(unsigned(b(4 downto 0)))));

  eq  <= and xor_ab;
  lt  <= '1' when to_integer(signed(a)) < to_integer(signed(b)) else '0';
  ltu <= less_than_u(a, b);
end Behavioral;
