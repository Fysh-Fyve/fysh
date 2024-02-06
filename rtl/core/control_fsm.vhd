--! \file control_fsm.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! The Big Brain of the CPU.\n

--! TODO: Implement
entity control_fsm is
  port (
    clk_i     : in std_ulogic;          --! Clock Signal.
    halt_i    : in std_ulogic;
    reset_i   : in std_ulogic;
    eq_i      : in std_ulogic;          --! Equal flag (A == B).
    lt_i      : in std_ulogic;          --! Less than flag (A < B).
    ltu_i     : in std_ulogic;  --! Unsigned less than flag (A < B (unsigned)).
    opcode_i  : in std_ulogic_vector (6 downto 0) := (others => '0');
    op_bits_i : in std_ulogic_vector (2 downto 0);
    sub_sra_i : in std_ulogic;  --! subtract or shift right arithmetic flag (0 = add, logical shift right; 1 = subtract, arithmetic shift right).

    op_bits_o : out std_ulogic_vector (2 downto 0) := (others => '0');
    rd_sel_o  : out std_ulogic_vector (1 downto 0) := (others => '0');

    sub_sra_o      : out std_ulogic := '0';
    addr_sel_o     : out std_ulogic := '0';
    alu_a_sel_o    : out std_ulogic := '0';
    alu_b_sel_o    : out std_ulogic := '0';
    mem_write_en_o : out std_ulogic := '0';
    rd_clk_o       : out std_ulogic := '0';
    pc_clk_o       : out std_ulogic := '0';
    ir_clk_o       : out std_ulogic := '0';
    pc_alu_sel_o   : out std_ulogic := '0';
    pc_next_sel_o  : out std_ulogic := '0';
    done_o         : out std_logic  := '0');  --! The CPU is done executing
end control_fsm;

architecture rtl of control_fsm is
  type state_t is (decode, drive, done);
  signal pc_clk       : std_ulogic := '0';
  signal ir_clk       : std_ulogic := '0';
  signal mem_write_en : std_ulogic := '0';

  signal state : state_t := decode;
begin

  drive_clock : process(clk_i, halt_i, opcode_i, pc_clk, ir_clk, mem_write_en)
    use std.textio.all;
    variable l : line;
  begin
    if falling_edge(reset_i) then
      state  <= decode;
      done_o <= '0';
    elsif rising_edge(halt_i) then
      state <= done;
    elsif clk_i'event then
      --! TODO: Decode kinda like 410
      case state is
        when decode =>
          alu_b_sel_o   <= not opcode_i(5);  -- immediate value ('1') or rs2 ('0')
          -- TODO: Figure this out
          alu_a_sel_o   <= opcode_i(0);      -- pc ('1') or rs1 ('0')
          addr_sel_o    <= opcode_i(0);      -- alu ('1') or pc ('0')
          pc_alu_sel_o  <= '1';         -- 4 ('1') or immediate value ('0')
          pc_next_sel_o <= opcode_i(0);      -- alu ('1') or pc alu ('0')
          rd_sel_o      <= opcode_i(1 downto 0);  -- mem_sx ("11"), alu ("01"), or pc alu ("00")

          sub_sra_o <= sub_sra_i;
          op_bits_o <= op_bits_i(2 downto 0);

          -- TODO!!
          rd_clk_o <= opcode_i(0);
          state    <= drive;
        when drive =>
          pc_clk       <= not pc_clk;
          ir_clk       <= not ir_clk;
          mem_write_en <= not mem_write_en;
          state        <= decode;
        when done =>
          done_o <= '1';
      end case;
    end if;
    pc_clk_o       <= pc_clk;
    ir_clk_o       <= ir_clk;
    mem_write_en_o <= mem_write_en;
  end process drive_clock;
end rtl;
