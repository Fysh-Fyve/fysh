--! \file control_fsm.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use work.fysh_fyve.all;
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
  type state_t is (init, decode, drive, done);
  signal pc_clk       : std_ulogic := '0';
  signal ir_clk       : std_ulogic := '0';
  signal rd_clk       : std_ulogic := '0';
  signal mem_write_en : std_ulogic := '0';

  signal write_mem : std_ulogic := '0';
  signal write_reg : std_ulogic := '0';

  signal state : state_t := init;
begin
  alu_a_sel_o <= opcode_i(2) and not opcode_i(5);
  alu_b_sel_o <= opcode_i(2) or not opcode_i(5);
  addr_sel_o  <= '1';

  with opcode_i(2) select op_bits_o <=
    OP_OR                 when '1',
    op_bits_i(2 downto 0) when others;
  sub_sra_o <= sub_sra_i and not opcode_i(2);

  drive_clock : process(clk_i, halt_i, opcode_i, pc_clk, ir_clk, mem_write_en)
    use std.textio.all;
    variable l : line;
  begin
    if falling_edge(reset_i) then
      state  <= init;
      done_o <= '0';
    elsif rising_edge(halt_i) then
      state <= done;
    elsif rising_edge(clk_i) then
      --! TODO: Decode kinda like 410
      case state is
        when init =>
          state <= decode;
        when decode =>
          case opcode_i(2) is
            when '1' =>                 -- LUI/AUIPC (for now!)
              -- TODO: Handle the case where it's not!
              rd_sel_o      <= "01";
              write_reg     <= '1';
              pc_alu_sel_o  <= '1';
              pc_next_sel_o <= '0';
            when others =>              -- The typical ALU stuff
              rd_sel_o      <= "01";  -- mem_sx ("11"), alu ("01"), or pc alu ("00")
              write_reg     <= '1';
              pc_alu_sel_o  <= '1';     -- 4 ('1') or immediate value ('0')
              pc_next_sel_o <= '0';     -- alu ('1') or pc alu ('0')
          end case;
          mem_write_en <= '0';
          rd_clk       <= '0';
          ir_clk       <= '1';
          pc_clk       <= '0';
          state        <= drive;
        when drive =>
          if (write_mem = '1') then
            mem_write_en <= '1';
            write_mem    <= '0';
          end if;
          if (write_reg = '1') then
            rd_clk    <= '1';
            write_reg <= '0';
          end if;
          ir_clk <= '0';
          pc_clk <= '1';
          state  <= decode;
        when done =>
          done_o <= '1';
      end case;
    end if;
  end process drive_clock;

  rd_clk_o       <= rd_clk;
  pc_clk_o       <= pc_clk;
  ir_clk_o       <= ir_clk;
  mem_write_en_o <= mem_write_en;
end rtl;
