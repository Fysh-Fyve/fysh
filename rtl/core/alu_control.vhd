--! \file alu_control.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! A higher-level module that combines the ALU and the Control FSM.\n

--! Also includes the Program Counter and the Immediate Value sign extender.
entity alu_control is
  port (
    clk_i         : in std_ulogic;      --! Clock signal.
    instruction_i : in std_ulogic_vector (31 downto 0);  --! Instruction to be executed.
    reg_val_1_i   : in std_ulogic_vector (31 downto 0);  --! Value from first selected register
    reg_val_2_i   : in std_ulogic_vector (31 downto 0);  --! Value from second selected register

    rd_clk_o       : out std_ulogic;    --! register file clock signal
    mem_write_en_o : out std_ulogic;    --! memory clock signal
    ir_clk_o       : out std_ulogic;    --! instruction register clock signal

    alu_o           : out std_ulogic_vector (31 downto 0);  --! ALU output
    pc_o            : out std_ulogic_vector (31 downto 0);  --! Program Counter output
    pc_alu_result_o : out std_ulogic_vector (31 downto 0);  --! Program Counter's ALU output

    reset_o    : out std_ulogic;        --! Reset signal
    addr_sel_o : out std_ulogic;        --! ALU & PC address select signal
    rd_sel_o   : out std_ulogic_vector (1 downto 0);  --! Register File write select
    sx_size_o  : out std_ulogic_vector (2 downto 0));  --! Memory fetch size
end alu_control;

architecture rtl of alu_control is
  -- Clock Signals
  signal pc_clk : std_ulogic := '0';

  -- Select signals
  signal pc_next_sel : std_ulogic                     := '0';
  signal pc_alu_sel  : std_ulogic                     := '0';
  signal sub_sra     : std_ulogic                     := '0';
  signal op_bits     : std_ulogic_vector (2 downto 0) := (others => '0');

  -- Result signals
  signal imm_ex   : std_ulogic_vector (31 downto 0) := (others => '0');
  signal alu_a_op : std_ulogic_vector (31 downto 0) := (others => '0');
  signal alu_b_op : std_ulogic_vector (31 downto 0) := (others => '0');
  signal eq       : std_ulogic                      := '0';
  signal lt       : std_ulogic                      := '0';
  signal ltu      : std_ulogic                      := '0';

  signal alu_a_sel : std_ulogic := '0';
  signal alu_b_sel : std_ulogic := '0';

  signal reset, addr_sel : std_ulogic;
  signal rd_sel          : std_ulogic_vector (1 downto 0);
  signal sx_size         : std_ulogic_vector (2 downto 0);
  signal alu, pc         : std_ulogic_vector (31 downto 0);
begin
  imm_sx_inst : entity work.imm_sx(rtl) port map (
    instruction_i => instruction_i,
    imm_val_o     => imm_ex);

  program_counter_inst : entity work.program_counter(rtl) port map (
    pc_clk_i        => pc_clk,
    reset_i         => reset,
    pc_next_sel_i   => pc_next_sel,
    pc_alu_sel_i    => pc_alu_sel,
    imm_x_i         => imm_ex,
    alu_i           => alu,
    pc_o            => pc,
    pc_alu_result_o => pc_alu_result_o);

  alu_inst : entity work.alu(rtl) port map (
    operand_a_i               => alu_a_op,
    operand_b_i               => alu_b_op,
    op_bits_i                 => op_bits,
    sub_sra_i                 => sub_sra,
    alu_result_o              => alu,
    equal_flag_o              => eq,
    less_than_flag_o          => lt,
    less_than_unsigned_flag_o => ltu);

  control_fsm_inst : entity work.control_fsm(rtl) port map(
    clk_i     => clk_i,
    eq_i      => eq,
    lt_i      => lt,
    ltu_i     => ltu,
    opcode_i  => instruction_i(6 downto 0),
    op_bits_i => instruction_i(14 downto 12),
    sub_sra_i => instruction_i(30),

    sub_sra_o      => sub_sra,
    op_bits_o      => op_bits,
    sx_size_o      => sx_size,
    addr_sel_o     => addr_sel,
    alu_a_sel_o    => alu_a_sel,
    alu_b_sel_o    => alu_b_sel,
    rd_sel_o       => rd_sel,
    mem_write_en_o => mem_write_en_o,
    rd_clk_o       => rd_clk_o,
    pc_clk_o       => pc_clk,
    ir_clk_o       => ir_clk_o,
    pc_alu_sel_o   => pc_alu_sel,
    pc_next_sel_o  => pc_next_sel,
    reset_o        => reset);

  reset_o    <= reset;
  addr_sel_o <= addr_sel;
  rd_sel_o   <= rd_sel;
  sx_size_o  <= sx_size;
  alu_o      <= alu;
  pc_o       <= pc;

  with alu_a_sel select alu_a_op <=
    reg_val_1_i     when '0',
    pc              when '1',
    (others => 'X') when others;

  with alu_b_sel select alu_b_op <=
    reg_val_2_i     when '0',
    imm_ex          when '1',
    (others => 'X') when others;
end rtl;
