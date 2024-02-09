--! \file alu_control_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use std.env.stop;
--! @endcond

--! Test bench for the ALU-Control module.
entity alu_control_tb is
end alu_control_tb;

architecture test_bench of alu_control_tb is
  signal insn    : std_ulogic_vector (31 downto 0) := (others => '0');
  signal rs1_val : std_ulogic_vector (31 downto 0) := (others => '0');
  signal rs2_val : std_ulogic_vector (31 downto 0) := (others => '0');

  -- Clock Signals
  signal clk          : std_ulogic := '0';
  signal rd_clk       : std_ulogic := '0';
  signal ir_clk       : std_ulogic := '0';
  signal mem_write_en : std_ulogic := '0';

  signal alu      : std_ulogic_vector (31 downto 0) := (others => '0');
  signal pc       : std_ulogic_vector (31 downto 0) := (others => '0');
  signal pc_alu   : std_ulogic_vector (31 downto 0) := (others => '0');
  signal rd_sel   : std_ulogic_vector (1 downto 0)  := (others => '0');
  signal reset    : std_ulogic                      := '0';
  signal addr_sel : std_ulogic                      := '0';

  signal rs1_or_zero : std_ulogic_vector (31 downto 0);
begin
  clock : process
  begin
    clk <= not clk;
    wait for 10.6383 ns;
  end process clock;


  alu_control_inst : entity work.alu_control(rtl) port map (
    clk_i           => clk,
    reset_i         => reset,
    instruction_i   => insn,
    reg_val_1_i     => rs1_or_zero,
    reg_val_2_i     => rs2_val,
    alu_o           => alu,
    pc_o            => pc,
    pc_alu_result_o => pc_alu,
    addr_sel_o      => addr_sel,
    rd_clk_o        => rd_clk,
    ir_clk_o        => ir_clk,
    mem_write_en_o  => mem_write_en,
    rd_sel_o        => rd_sel);

  main : process
    use std.textio.all;
    variable l : line;
  begin
    wait for 1 us;
    stop;
  end process main;
end test_bench;
