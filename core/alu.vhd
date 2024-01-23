--! \file alu.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.alu_operations.all;
--! @endcond

-- Before I forget and have to scour Google for this again
-- https://nandland.com/common-vhdl-conversions/

--! The Arithmetic Logic Unit of the CPU.\n

--! Performs typical basic ALU operations like add, subtract, shift, and, or,
--! xor, and signed and unsigned comparisons.
entity alu is
  port (
    --! First operand in the ALU.
    operand_a_i               : in  std_ulogic_vector (31 downto 0);
    --! Second operand in the ALU.
    operand_b_i               : in  std_ulogic_vector (31 downto 0);
    --! Determines the operation to perform.
    op_bits_i                 : in  std_ulogic_vector (2 downto 0);
    --! Modifies the ADD and SHIFT_RIGHT operations.\n ADD becomes SUB, SHIFT_RIGHT changes from logical to arithmetic shift.
    add_shift_modify_flag_i   : in  std_ulogic;
    --! Result of the ALU.
    alu_result_o              : out std_ulogic_vector (31 downto 0);
    --! Set if `operand_a_i` == `operand_b_i`.
    equal_flag_o              : out std_ulogic;
    --! Set if `operand_a_i` < `operand_b_i` as signed 32-bit integers.
    less_than_flag_o          : out std_ulogic;
    --! Set if `operand_a_i` < `operand_b_i` as unsigned 32-bit integers.
    less_than_unsigned_flag_o : out std_ulogic);
end alu;


architecture Behavioral of alu is
  signal add_sub_result   : signed (31 downto 0);
  signal left_shifted     : std_ulogic_vector (31 downto 0);
  signal right_shifted    : std_ulogic_vector (31 downto 0);
  signal unsigned_shift_a : std_ulogic_vector (31 downto 0);
  signal signed_shift_a   : std_ulogic_vector (31 downto 0);

  function int_from_bit(x : std_ulogic)
    return std_ulogic_vector is
  begin
    return x"0000000" & "000" & x;
  end function int_from_bit;

  function less_than_unsigned(
    a : std_ulogic_vector (31 downto 0);
    b : std_ulogic_vector (31 downto 0)) return std_ulogic is
    variable a_int : integer;
    variable b_int : integer;
    variable lt    : std_ulogic;
  begin
    a_int := to_integer(unsigned(a(30 downto 0)));
    b_int := to_integer(unsigned(b(30 downto 0)));
    lt    := '1' when a_int < b_int else '0';
    return (not a(31) and b(31)) or (lt and (a(31) xnor b(31)));
  end function less_than_unsigned;

  function less_than_signed(
    a : std_ulogic_vector (31 downto 0);
    b : std_ulogic_vector (31 downto 0)) return std_ulogic is
    variable a_int : integer;
    variable b_int : integer;
    variable ltu   : std_ulogic;
  begin
    a_int := to_integer(signed(a));
    b_int := to_integer(signed(b));
    ltu   := '1' when a_int < b_int else '0';
    return ltu;
  end function less_than_signed;
begin
  with op_bits_i select alu_result_o <=
    operand_a_i and operand_b_i             when OP_AND,
    operand_a_i or operand_b_i              when OP_OR,
    right_shifted                           when OP_SHIFT_RIGHT,
    operand_a_i xor operand_b_i             when OP_XOR,
    int_from_bit(less_than_unsigned_flag_o) when OP_LESS_THAN_UNSIGNED,
    int_from_bit(less_than_flag_o)          when OP_LESS_THAN,
    left_shifted                            when OP_SHIFT_LEFT,
    std_ulogic_vector(add_sub_result)       when OP_ADD_SUB,
    (others => 'X')                         when others;

  add_sub_result <= (signed(operand_a_i) - signed(operand_b_i))
                    when add_shift_modify_flag_i
                    else (signed(operand_a_i) + signed(operand_b_i));

  left_shifted <= std_ulogic_vector(
    shift_left(
      unsigned(operand_a_i),
      to_integer(unsigned(operand_b_i(4 downto 0)))));

  right_shifted <= signed_shift_a
                   when add_shift_modify_flag_i
                   else unsigned_shift_a;

  unsigned_shift_a <= std_ulogic_vector(
    shift_right(
      unsigned(operand_a_i),
      to_integer(unsigned(operand_b_i(4 downto 0)))));

  signed_shift_a <= std_ulogic_vector(
    shift_right(
      signed(operand_a_i),
      to_integer(unsigned(operand_b_i(4 downto 0)))));

  equal_flag_o <= and (operand_a_i xnor operand_b_i);

  less_than_flag_o          <= less_than_signed(operand_a_i, operand_b_i);
  less_than_unsigned_flag_o <= less_than_unsigned(operand_a_i, operand_b_i);
end Behavioral;
