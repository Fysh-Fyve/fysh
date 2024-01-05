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
  signal pc_clk_s : std_ulogic := '0';

  -- Select signals
  signal pc_next_sel_s : std_ulogic                     := '0';
  signal pc_alu_sel_s  : std_ulogic                     := '0';
  signal sub_sra_s     : std_ulogic                     := '0';
  signal func_s        : std_ulogic_vector (2 downto 0) := (others => '0');

  -- Result signals
  signal imm_x_s : std_ulogic_vector (31 downto 0) := (others => '0');
  signal alu_a_s : std_ulogic_vector (31 downto 0) := (others => '0');
  signal alu_b_s : std_ulogic_vector (31 downto 0) := (others => '0');
  signal eq_s    : std_ulogic                      := '0';
  signal lt_s    : std_ulogic                      := '0';
  signal ltu_s   : std_ulogic                      := '0';

  signal alu_a_sel_s : std_ulogic := '0';
  signal alu_b_sel_s : std_ulogic := '0';
begin
  imm_sx_u : component imm_sx port map (
    insn_i  => insn_i,
    imm_x_o => imm_x_s);

  program_counter_u : component program_counter port map (
    pc_clk_i      => pc_clk_s,
    reset_i       => reset_o,
    pc_next_sel_i => pc_next_sel_s,
    pc_alu_sel_i  => pc_alu_sel_s,
    imm_x_i       => imm_x_s,
    alu_i         => alu_o,
    pc_o          => pc_o,
    pc_alu_o      => pc_alu_o);

  alu_u : component alu port map (
    a_i       => alu_a_s,
    b_i       => alu_b_s,
    func_i    => func_s,
    sub_sra_i => sub_sra_s,
    q_o       => alu_o,
    eq_o      => eq_s,
    lt_o      => lt_s,
    ltu_o     => ltu_s);

  control_fsm_u : component control_fsm port map(
    clk_i     => clk_i,
    eq_i      => eq_s,
    lt_i      => lt_s,
    ltu_i     => ltu_s,
    opcode_i  => insn_i(6 downto 0),
    funct3_i  => insn_i(14 downto 12),
    sub_sra_i => insn_i(30),

    sub_sra_o     => sub_sra_s,
    func_o        => func_s,
    sx_size_o     => sx_size_o,
    addr_sel_o    => addr_sel_o,
    alu_a_sel_o   => alu_a_sel_s,
    alu_b_sel_o   => alu_b_sel_s,
    rd_sel_o      => rd_sel_o,
    mem_clk_o     => mem_clk_o,
    rd_clk_o      => rd_clk_o,
    pc_clk_o      => pc_clk_s,
    ir_clk_o      => ir_clk_o,
    pc_alu_sel_o  => pc_alu_sel_s,
    pc_next_sel_o => pc_next_sel_s,
    reset_o       => reset_o);

  with alu_a_sel_s select alu_a_s <=
    rs1_val_i       when '0',
    pc_o            when '1',
    (others => 'X') when others;

  with alu_b_sel_s select alu_b_s <=
    rs2_val_i       when '0',
    imm_x_s         when '1',
    (others => 'X') when others;
end Behavioral;
