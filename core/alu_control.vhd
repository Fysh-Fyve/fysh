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
    --! The clock signal.
    clk_i           : in std_ulogic;
    --! The 32-bit instruction.
    instruction_i   : in std_ulogic_vector (31 downto 0);
    --! The first selected value from the Register File.
    reg_sel_1_val_i : in std_ulogic_vector (31 downto 0);
    --! The second selected value from the Register File.
    reg_sel_2_val_i : in std_ulogic_vector (31 downto 0);

    --! Clock signal output that drives the register file.
    rd_clk_o  : out std_ulogic;
    --! Clock signal output that drives the memory.
    mem_clk_o : out std_ulogic;
    --! Clock signal output that drives the instruction register.
    ir_clk_o  : out std_ulogic;

    --! The output of the ALU.
    alu_o           : out std_ulogic_vector (31 downto 0);
    --! The output of the Program Counter.
    pc_o            : out std_ulogic_vector (31 downto 0);
    --! The output of the Program Counter's ALU.
    pc_alu_result_o : out std_ulogic_vector (31 downto 0);

    --! The reset signal.
    reset_o    : out std_ulogic;
    --! Flag to select the read/write address either from the ALU or the PC.
    addr_sel_o : out std_ulogic;
    --! Determines what value is going to be written into the register file.
    rd_sel_o   : out std_ulogic_vector (1 downto 0);
    --! Determines the size of the value to be fetched from memory.
    sx_size_o  : out std_ulogic_vector (2 downto 0));
end alu_control;

architecture Behavioral of alu_control is
  component control_fsm is port (
    clk_i                   : in std_ulogic;
    eq_i, lt_i, ltu_i       : in std_ulogic;
    opcode_i                : in std_ulogic_vector (6 downto 0);
    op_bits_i               : in std_ulogic_vector (2 downto 0);
    add_shift_modify_flag_i : in std_ulogic;

    -- Clock signals
    mem_clk_o, rd_clk_o : out std_ulogic;
    pc_clk_o, ir_clk_o  : out std_ulogic;

    -- Select signals
    addr_sel_o                  : out std_ulogic;
    pc_alu_sel_o, pc_next_sel_o : out std_ulogic;
    alu_a_sel_o, alu_b_sel_o    : out std_ulogic;

    add_shift_modify_flag_o : out std_ulogic;
    op_bits_o, sx_size_o    : out std_ulogic_vector (2 downto 0);
    rd_sel_o                : out std_ulogic_vector (1 downto 0);
    reset_o                 : out std_logic);
  end component;

  component alu is port (
    operand_a_i, operand_b_i : in std_ulogic_vector (31 downto 0);
    op_bits_i                : in std_ulogic_vector (2 downto 0);
    add_shift_modify_flag_i  : in std_ulogic;

    alu_result_o                                              : out std_ulogic_vector (31 downto 0);
    equal_flag_o, less_than_flag_o, less_than_unsigned_flag_o : out std_ulogic);
  end component;

  component imm_sx is port (
    instruction_i : in  std_ulogic_vector (31 downto 0);
    imm_x_o       : out std_ulogic_vector (31 downto 0));
  end component;

  component program_counter is port (
    pc_clk_i, reset_i, pc_next_sel_i, pc_alu_sel_i : in std_ulogic;

    imm_x_i, alu_i        : in  std_ulogic_vector (31 downto 0);
    pc_o, pc_alu_result_o : out std_ulogic_vector (31 downto 0));
  end component;

  -- Clock Signals
  signal pc_clk : std_ulogic := '0';

  -- Select signals
  signal pc_next_sel           : std_ulogic                     := '0';
  signal pc_alu_sel            : std_ulogic                     := '0';
  signal add_shift_modify_flag : std_ulogic                     := '0';
  signal op_bits               : std_ulogic_vector (2 downto 0) := (others => '0');

  -- Result signals
  signal imm_ex   : std_ulogic_vector (31 downto 0) := (others => '0');
  signal alu_a_op : std_ulogic_vector (31 downto 0) := (others => '0');
  signal alu_b_op : std_ulogic_vector (31 downto 0) := (others => '0');
  signal eq       : std_ulogic                      := '0';
  signal lt       : std_ulogic                      := '0';
  signal ltu      : std_ulogic                      := '0';

  signal alu_a_sel : std_ulogic := '0';
  signal alu_b_sel : std_ulogic := '0';
begin
  imm_sx_inst : component imm_sx port map (
    instruction_i => instruction_i,
    imm_x_o       => imm_ex);

  program_counter_inst : component program_counter port map (
    pc_clk_i        => pc_clk,
    reset_i         => reset_o,
    pc_next_sel_i   => pc_next_sel,
    pc_alu_sel_i    => pc_alu_sel,
    imm_x_i         => imm_ex,
    alu_i           => alu_o,
    pc_o            => pc_o,
    pc_alu_result_o => pc_alu_result_o);

  alu_inst : component alu port map (
    operand_a_i               => alu_a_op,
    operand_b_i               => alu_b_op,
    op_bits_i                 => op_bits,
    add_shift_modify_flag_i   => add_shift_modify_flag,
    alu_result_o              => alu_o,
    equal_flag_o              => eq,
    less_than_flag_o          => lt,
    less_than_unsigned_flag_o => ltu);

  control_fsm_inst : component control_fsm port map(
    clk_i                   => clk_i,
    eq_i                    => eq,
    lt_i                    => lt,
    ltu_i                   => ltu,
    opcode_i                => instruction_i(6 downto 0),
    op_bits_i               => instruction_i(14 downto 12),
    add_shift_modify_flag_i => instruction_i(30),

    add_shift_modify_flag_o => add_shift_modify_flag,
    op_bits_o               => op_bits,
    sx_size_o               => sx_size_o,
    addr_sel_o              => addr_sel_o,
    alu_a_sel_o             => alu_a_sel,
    alu_b_sel_o             => alu_b_sel,
    rd_sel_o                => rd_sel_o,
    mem_clk_o               => mem_clk_o,
    rd_clk_o                => rd_clk_o,
    pc_clk_o                => pc_clk,
    ir_clk_o                => ir_clk_o,
    pc_alu_sel_o            => pc_alu_sel,
    pc_next_sel_o           => pc_next_sel,
    reset_o                 => reset_o);

  with alu_a_sel select alu_a_op <=
    reg_sel_1_val_i when '0',
    pc_o            when '1',
    (others => 'X') when others;

  with alu_b_sel select alu_b_op <=
    reg_sel_2_val_i when '0',
    imm_ex          when '1',
    (others => 'X') when others;
end Behavioral;
