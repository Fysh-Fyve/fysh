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
  signal clk       : std_ulogic;        --! Clock Signal.
  signal eq        : std_ulogic;        --! Equal flag (A == B).
  signal lt        : std_ulogic;        --! Less than flag (A < B).
  signal ltu       : std_ulogic;  --! Unsigned less than flag (A < B (unsigned)).
  signal opcode    : std_ulogic_vector (6 downto 0);
  signal op_bits_i : std_ulogic_vector (2 downto 0);
  signal op_bits_o : std_ulogic_vector (2 downto 0);
  signal sub_sra_i : std_ulogic;  -- subtract or shift right arithmetic flag (0 = add, logical shift right; 1 = subtract, arithmetic shift right).
  signal sub_sra_o : std_ulogic;

  signal rd_sel : std_ulogic_vector (1 downto 0) := (others => '0');

  signal raddr_sel     : std_ulogic := '0';
  signal waddr_sel     : std_ulogic := '0';
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
  control_fsm_inst : entity work.control_fsm(rtl) port map (
    clk_i     => clk,
    reset_i   => reset,
    eq_i      => eq,
    lt_i      => lt,
    ltu_i     => ltu,
    opcode_i  => opcode,
    op_bits_i => op_bits_i,
    sub_sra_i => sub_sra_i,

    op_bits_o => op_bits_o,
    rd_sel_o  => rd_sel,

    sub_sra_o      => sub_sra_o,
    raddr_sel_o    => raddr_sel,
    waddr_sel_o    => waddr_sel,
    alu_a_sel_o    => alu_a_sel,
    alu_b_sel_o    => alu_b_sel,
    mem_write_en_o => mem_write_en,
    rd_clk_o       => rd_clk,
    pc_clk_o       => pc_clk,
    ir_clk_o       => ir_clk,
    pc_alu_sel_o   => pc_alu_sel,
    pc_next_sel_o  => pc_next_sel);
  main : process
    use std.textio.all;
    variable my_line : line;
  begin
    clk   <= '0';
    reset <= '1';
    wait for 10.6383 ns;
    clk   <= '1';
    reset <= '0';
    wait for 10.6383 ns;
    clk   <= '0';
    reset <= '1';
    wait for 10.6383 ns;
    stop;
  end process main;

  rep : process(clk)
  begin
    if clk'event then
      report "clk = " & to_string(clk)
        & ", opcode = " & to_string(opcode)
        & ", rd_sel = " & to_string(rd_sel)
        & ", sub_sra_o = " & to_string(sub_sra_o)
        & ", raddr_sel = " & to_string(raddr_sel)
        & ", waddr_sel = " & to_string(waddr_sel)
        & ", alu_a_sel = " & to_string(alu_a_sel)
        & ", alu_b_sel = " & to_string(alu_b_sel)
        & ", mem_write_en = " & to_string(mem_write_en)
        & ", rd_clk = " & to_string(rd_clk)
        & ", pc_clk = " & to_string(pc_clk)
        & ", ir_clk = " & to_string(ir_clk)
        & ", pc_alu_sel = " & to_string(pc_alu_sel)
        & ", pc_next_sel = " & to_string(pc_next_sel)
;
    end if;
  end process rep;
end test_bench;
