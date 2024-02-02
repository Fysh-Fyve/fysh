--! \file control_fsm_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use std.env.stop;
--! @endcond

--! Test bench for the Control Finite State Machine module.
entity control_fsm_tb is
end control_fsm_tb;

architecture test_bench of control_fsm_tb is
  signal clk     : std_ulogic;          --! Clock Signal.
  signal eq      : std_ulogic;          --! Equal flag (A == B).
  signal lt      : std_ulogic;          --! Less than flag (A < B).
  signal ltu     : std_ulogic;  --! Unsigned less than flag (A < B (unsigned)).
  signal opcode  : std_ulogic_vector (6 downto 0);
  signal op_bits : std_ulogic_vector (2 downto 0);
  signal sub_sra : std_ulogic;  -- subtract or shift right arithmetic flag (0 = add, logical shift right; 1 = subtract, arithmetic shift right).

  signal sx_size : std_ulogic_vector (2 downto 0) := (others => '0');
  signal rd_sel  : std_ulogic_vector (1 downto 0) := (others => '0');

  signal addr_sel     : std_ulogic := '0';
  signal alu_a_sel    : std_ulogic := '0';
  signal alu_b_sel    : std_ulogic := '0';
  signal mem_write_en : std_ulogic := '0';
  signal rd_clk       : std_ulogic := '0';
  signal pc_clk       : std_ulogic := '0';
  signal ir_clk       : std_ulogic := '0';
  signal pc_alu_sel   : std_ulogic := '0';
  signal pc_next_sel  : std_ulogic := '0';
  signal reset        : std_logic  := '0';
begin
  clock : process
  begin
    clk <= not clk;
    wait for 1 ns;
  end process clock;

  control_fsm_inst : entity work.control_fsm(rtl) port map (
    clk_i     => clk,
    eq_i      => eq,
    lt_i      => lt,
    ltu_i     => ltu,
    opcode_i  => opcode,
    op_bits_i => op_bits,
    sub_sra_i => sub_sra,

    op_bits_o => op_bits,
    sx_size_o => sx_size,
    rd_sel_o  => rd_sel,

    sub_sra_o      => sub_sra,
    addr_sel_o     => addr_sel,
    alu_a_sel_o    => alu_a_sel,
    alu_b_sel_o    => alu_b_sel,
    mem_write_en_o => mem_write_en,
    rd_clk_o       => rd_clk,
    pc_clk_o       => pc_clk,
    ir_clk_o       => ir_clk,
    pc_alu_sel_o   => pc_alu_sel,
    pc_next_sel_o  => pc_next_sel,
    reset_o        => reset);
  main : process
    use std.textio.all;
    variable my_line : line;
  begin
    wait for 200 ns;
    stop;
  end process main;
end test_bench;
