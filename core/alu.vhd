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
    operand_a_i, operand_b_i  : in  std_ulogic_vector (31 downto 0); --! input operands
    op_bits_i                 : in  std_ulogic_vector (2 downto 0);  --! Determines the operation to perform.
    sub_sra_i                 : in  std_ulogic;                      --! Control signal for subtraction/arithmetic right shift
    alu_result_o              : out std_ulogic_vector (31 downto 0); --! Result of the operation.
    equal_flag_o              : out std_ulogic;                      --! `operand_a_i` == `operand_b_i`.
    less_than_flag_o          : out std_ulogic;                      --! `operand_a_i` < `operand_b_i`
    less_than_unsigned_flag_o : out std_ulogic);                     --! `operand_a_i` < `operand_b_i`
end alu;


architecture Behavioral of alu is
  signal add_sub_result   : signed (31 downto 0);
  signal left_shifted     : std_ulogic_vector (31 downto 0);
  signal right_shifted    : std_ulogic_vector (31 downto 0);
  signal unsigned_shift_a : std_ulogic_vector (31 downto 0);
  signal signed_shift_a   : std_ulogic_vector (31 downto 0);
  signal lt_unsigned_flag : std_ulogic;
  signal lt_signed_flag   : std_ulogic;

  -- converts a std_ulogic to a std_ulogic_vector (32 bits)
  function int_from_bit(x : std_ulogic) return std_ulogic_vector is
    begin
      return (31 downto 1 => '0') & x;
    end function int_from_bit;
  
  --! checks if `a` is less than `b` when both are unsigned
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
    return (not a(31) and b(31)) or (lt and (a(31) xnor b(31))); -- why is there a sign check if its unsigned?
  end function less_than_unsigned;
  
  -- checks if `a` is less than `b` when both are signed
  function less_than_signed(
    a : std_ulogic_vector (31 downto 0);
    b : std_ulogic_vector (31 downto 0)) return std_ulogic is
  begin
      if to_integer(signed(a)) < to_integer(signed(b)) then
        return '1';
      else
        return '0';
      end if;
  end function less_than_signed;


begin
  -- select operation
  with op_bits_i select alu_result_o <=
    operand_a_i and operand_b_i             when OP_AND,
    operand_a_i or operand_b_i              when OP_OR,
    right_shifted                           when OP_SHIFT_RIGHT,
    operand_a_i xor operand_b_i             when OP_XOR,
    int_from_bit(lt_unsigned_flag)          when OP_LESS_THAN_UNSIGNED,
    int_from_bit(lt_signed_flag)            when OP_LESS_THAN,
    left_shifted                            when OP_SHIFT_LEFT,
    std_ulogic_vector(add_sub_result)       when OP_ADD_SUB,
    (others => 'X')                         when others;

  add_sub_result <= (signed(operand_a_i) - signed(operand_b_i))
                    when sub_sra_i -- expects boolen, not std_ulogic. is there a reason you used std_ulogic?
                    else (signed(operand_a_i) + signed(operand_b_i));

  left_shifted <= std_ulogic_vector(
    shift_left(
      unsigned(operand_a_i),
      to_integer(unsigned(operand_b_i(4 downto 0)))));

  right_shifted <= signed_shift_a
                   when sub_sra_i -- expects boolen, not std_ulogic. is there a reason you used std_ulogic?
                   else unsigned_shift_a;

  unsigned_shift_a <= std_ulogic_vector(
    shift_right(
      unsigned(operand_a_i),
      to_integer(unsigned(operand_b_i(4 downto 0)))));

  signed_shift_a <= std_ulogic_vector(
    shift_right(
      signed(operand_a_i),
      to_integer(unsigned(operand_b_i(4 downto 0)))));

  -- set flags
  equal_flag_o              <= '1' when operand_a_i = operand_b_i else '0';
  lt_unsigned_flag          <= less_than_unsigned(operand_a_i, operand_b_i);
  lt_signed_flag            <= less_than_signed(operand_a_i, operand_b_i);
  less_than_flag_o          <= lt_signed_flag;
  less_than_unsigned_flag_o <= lt_unsigned_flag;
end Behavioral;
