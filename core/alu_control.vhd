library ieee;
use ieee.std_logic_1164.all;

entity alu_control is
  port (
    clk_i                : in std_ulogic;
    insn_i               : in std_ulogic_vector (31 downto 0);
    rs1_val_i, rs2_val_i : in std_ulogic_vector (31 downto 0);

    -- Clock outputs
    rd_clk_o  : out std_ulogic;
    mem_clk_o : out std_ulogic;
    ir_clk_o  : out std_ulogic;

    alu_o, pc_o, pc_alu_o : out std_ulogic_vector (31 downto 0);
    reset_o, addr_sel_o   : out std_ulogic;
    rd_sel_o              : out std_ulogic_vector (1 downto 0);
    sx_size_o             : out std_ulogic_vector (2 downto 0));
end alu_control;

architecture Behavioral of alu_control is
  component control_fsm is port (
    clk_i             : in std_ulogic;
    eq_i, lt_i, ltu_i : in std_ulogic;
    opcode_i          : in std_ulogic_vector (6 downto 0);
    funct3_i          : in std_ulogic_vector (2 downto 0);
    sub_sra_i         : in std_ulogic;

    -- Clock signals
    mem_clk_o, rd_clk_o : out std_ulogic;
    pc_clk_o, ir_clk_o  : out std_ulogic;

    -- Select signals
    addr_sel_o                  : out std_ulogic;
    pc_alu_sel_o, pc_next_sel_o : out std_ulogic;
    alu_a_sel_o, alu_b_sel_o    : out std_ulogic;

    sub_sra_o         : out std_ulogic;
    func_o, sx_size_o : out std_ulogic_vector (2 downto 0);
    rd_sel_o          : out std_ulogic_vector (1 downto 0);
    reset_o           : out std_logic);
  end component;

  component alu is port (
    a_i, b_i  : in std_ulogic_vector (31 downto 0);
    func_i    : in std_ulogic_vector (2 downto 0);
    sub_sra_i : in std_ulogic;

    q_o               : out std_ulogic_vector (31 downto 0);
    eq_o, lt_o, ltu_o : out std_ulogic);
  end component;

  component imm_sx is port (
    insn_i  : in  std_ulogic_vector (31 downto 0);
    imm_x_o : out std_ulogic_vector (31 downto 0));
  end component;

  component program_counter is port (
    pc_clk_i, reset_i, pc_next_sel_i, pc_alu_sel_i : in std_ulogic;

    imm_x_i, alu_i : in  std_ulogic_vector (31 downto 0);
    pc_o, pc_alu_o : out std_ulogic_vector (31 downto 0));
  end component;

  -- Clock Signals
  signal pc_clk : std_ulogic := '0';

  -- Select signals
  signal pc_next_sel : std_ulogic                     := '0';
  signal pc_alu_sel  : std_ulogic                     := '0';
  signal sub_sra     : std_ulogic                     := '0';
  signal func        : std_ulogic_vector (2 downto 0) := (others => '0');

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
    insn_i  => insn_i,
    imm_x_o => imm_ex);

  program_counter_inst : component program_counter port map (
    pc_clk_i      => pc_clk,
    reset_i       => reset_o,
    pc_next_sel_i => pc_next_sel,
    pc_alu_sel_i  => pc_alu_sel,
    imm_x_i       => imm_ex,
    alu_i         => alu_o,
    pc_o          => pc_o,
    pc_alu_o      => pc_alu_o);

  alu_inst : component alu port map (
    a_i       => alu_a_op,
    b_i       => alu_b_op,
    func_i    => func,
    sub_sra_i => sub_sra,
    q_o       => alu_o,
    eq_o      => eq,
    lt_o      => lt,
    ltu_o     => ltu);

  control_fsm_inst : component control_fsm port map(
    clk_i     => clk_i,
    eq_i      => eq,
    lt_i      => lt,
    ltu_i     => ltu,
    opcode_i  => insn_i(6 downto 0),
    funct3_i  => insn_i(14 downto 12),
    sub_sra_i => insn_i(30),

    sub_sra_o     => sub_sra,
    func_o        => func,
    sx_size_o     => sx_size_o,
    addr_sel_o    => addr_sel_o,
    alu_a_sel_o   => alu_a_sel,
    alu_b_sel_o   => alu_b_sel,
    rd_sel_o      => rd_sel_o,
    mem_clk_o     => mem_clk_o,
    rd_clk_o      => rd_clk_o,
    pc_clk_o      => pc_clk,
    ir_clk_o      => ir_clk_o,
    pc_alu_sel_o  => pc_alu_sel,
    pc_next_sel_o => pc_next_sel,
    reset_o       => reset_o);

  with alu_a_sel select alu_a_op <=
    rs1_val_i       when '0',
    pc_o            when '1',
    (others => 'X') when others;

  with alu_b_sel select alu_b_op <=
    rs2_val_i       when '0',
    imm_ex          when '1',
    (others => 'X') when others;
end Behavioral;
