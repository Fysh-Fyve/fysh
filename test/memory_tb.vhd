--! \file memory_tb.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! Test bench for the high-level memory module.
entity memory_tb is
end memory_tb;

architecture test_bench of memory_tb is
  signal clk, rd_clk, write_en, insn_clk, addr_sel, reset : std_ulogic;
  signal sx_size                                          : std_ulogic_vector (2 downto 0);
  signal rd_sel                                           : std_ulogic_vector (1 downto 0);
  signal alu, pc, pc_alu, insn, rs1_val, rs2_val          : std_ulogic_vector (31 downto 0);
begin
  memory_inst : entity work.memory(rtl) port map (
    clk_i          => clk,
    rd_clk_i     => rd_clk,
    write_en_i   => write_en,
    insn_clk_i   => insn_clk,
    addr_sel_i   => addr_sel,
    reset_i      => reset,
    sx_size_i    => sx_size,
    rd_sel_i     => rd_sel,
    alu_out_i    => alu,
    pc_out_i     => pc,
    pc_alu_out_i => pc_alu,
    insn_o       => insn,
    reg_val_1_o  => rs1_val,
    reg_val_2_o  => rs2_val);
end test_bench;
