--! \file topmodule.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! The top module that brings all the components together.\n
entity topmodule is
  port (clk : in std_ulogic);
end topmodule;

architecture rtl of topmodule is
  signal insn             : std_ulogic_vector (31 downto 0) := (others => '0');
  signal rs1_val, rs2_val : std_ulogic_vector (31 downto 0) := (others => '0');

  signal alu, pc, pc_alu                               : std_ulogic_vector (31 downto 0) := (others => '0');
  signal reset, addr_sel, rd_clk, mem_write_en, ir_clk : std_ulogic                      := '0';
  signal rd_sel                                        : std_ulogic_vector (1 downto 0)  := (others => '0');
  signal sx_size                                       : std_ulogic_vector (2 downto 0)  := (others => '0');
begin
  alu_control_inst : entity work.alu_control(rtl) port map (
    clk_i           => clk,
    instruction_i   => insn,
    reg_val_1_i     => rs1_val,
    reg_val_2_i     => rs2_val,
    alu_o           => alu,
    pc_o            => pc,
    pc_alu_result_o => pc_alu,
    reset_o         => reset,
    addr_sel_o      => addr_sel,
    rd_clk_o        => rd_clk,
    mem_write_en_o  => mem_write_en,
    ir_clk_o        => ir_clk,
    rd_sel_o        => rd_sel,
    sx_size_o       => sx_size);

  memory_inst : entity work.memory(rtl) port map (
    clk          => clk,
    rd_clk_i     => rd_clk,
    write_en_i   => mem_write_en,
    insn_clk_i   => ir_clk,
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
end rtl;
