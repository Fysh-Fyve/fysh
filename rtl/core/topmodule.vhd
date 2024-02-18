--! \file topmodule.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use work.fysh_fyve.all;
--! @endcond

--! The top module that brings all the components together.\n
entity topmodule is
  port (
    clk   : in    std_ulogic;
    reset : in    std_ulogic;
    done  : out   std_ulogic;
    gpio  : inout std_ulogic_vector (31 downto 0));
end topmodule;

architecture rtl of topmodule is
  signal insn             : std_ulogic_vector (31 downto 0);
  signal rs1_val, rs2_val : std_ulogic_vector (31 downto 0) := (others => '0');

  signal pc_alu : std_ulogic_vector (31 downto 0) := (others => '0');

  signal mem_write_en : std_ulogic := '0';
  signal ir_clk       : std_ulogic := '0';

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

  signal rs1_or_zero : std_ulogic_vector (31 downto 0) := (others => '0');

  signal alu_a_sel : std_ulogic := '0';
  signal alu_b_sel : std_ulogic := '0';

  signal draddr_sel : std_ulogic                      := '0';
  signal iraddr_sel : std_ulogic                      := '0';
  signal waddr_sel  : std_ulogic                      := '0';
  signal rd_clk     : std_ulogic                      := '0';
  signal rd_sel     : std_ulogic_vector (1 downto 0)  := (others => '0');
  signal alu        : std_ulogic_vector (31 downto 0) := (others => '0');
  signal pc         : std_ulogic_vector (31 downto 0) := (others => '0');

  signal rd_val                            : std_ulogic_vector (31 downto 0);
  signal iraddr, draddr                    : std_ulogic_vector (31 downto 0);
  signal waddr, dmem_out, imem_out, mem_sx : std_ulogic_vector (31 downto 0);
begin
  print : process(clk)
    use std.textio.all;
    variable l : line;
  begin
    if rising_edge(clk) then
      write(l, string'("pc_clk: "));
      write(l, pc_clk);
      write(l, string'(" rd_clk: "));
      write(l, rd_clk);
      write(l, string'(" pc: "));
      write(l, to_hstring(pc));
      write(l, string'(" ins: "));
      write(l, to_hstring(insn));
      write(l, string'(" func3: "));
      write_func3(l, op_bits);
      write(l, string'(" opcode: "));
      write_opcode(l, insn(6 downto 2));
      write(l, string'(" alu_a_op: "));
      write(l, to_hstring(alu_a_op));
      write(l, string'(" alu_b_op: "));
      write(l, to_hstring(alu_b_op));
      write(l, string'(" alu_o: "));
      write(l, to_hstring(alu));
      write(l, string'(" rd_sel: "));
      write(l, rd_sel);
      writeline(output, l);
      writeline(output, l);
    end if;
  end process print;

  imm_sx_inst : entity work.imm_sx(rtl) port map (
    instruction_i => insn,
    imm_val_o     => imm_ex);

  -- Hacky way to make rs1_val hardwire to 0
  with insn(6 downto 2) select rs1_or_zero <=
    (others => '0') when "01101",
    rs1_val         when others;

  program_counter_inst : entity work.program_counter(rtl) port map (
    pc_clk_i        => pc_clk,
    reset_i         => reset,
    pc_next_sel_i   => pc_next_sel,
    pc_alu_sel_i    => pc_alu_sel,
    imm_x_i         => imm_ex,
    alu_i           => alu,
    pc_o            => pc,
    pc_alu_result_o => pc_alu);

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
    clk_i     => clk,
    reset_i   => reset,
    eq_i      => eq,
    lt_i      => lt,
    ltu_i     => ltu,
    opcode_i  => insn(6 downto 0),
    op_bits_i => insn(14 downto 12),
    sub_sra_i => insn(30),

    sub_sra_o      => sub_sra,
    op_bits_o      => op_bits,
    waddr_sel_o    => waddr_sel,
    iraddr_sel_o   => iraddr_sel,
    draddr_sel_o   => draddr_sel,
    alu_a_sel_o    => alu_a_sel,
    alu_b_sel_o    => alu_b_sel,
    rd_sel_o       => rd_sel,
    mem_write_en_o => mem_write_en,
    rd_clk_o       => rd_clk,
    pc_clk_o       => pc_clk,
    ir_clk_o       => ir_clk,
    pc_alu_sel_o   => pc_alu_sel,
    pc_next_sel_o  => pc_next_sel);


  with alu_a_sel select alu_a_op <=
    rs1_or_zero     when '0',
    pc              when '1',
    (others => 'X') when others;

  with alu_b_sel select alu_b_op <=
    rs2_val         when '0',
    imm_ex          when '1',
    (others => 'X') when others;

  mem_inst : entity work.phy_map(rtl) port map (
    clk_i      => clk,
    draddr_i   => draddr,
    iraddr_i   => iraddr,
    waddr_i    => waddr,
    write_en_i => mem_write_en,
    d_i        => rs2_val,
    d_o        => dmem_out,
    i_o        => imem_out,
    gpio       => gpio
    );

  mbr_sx_inst : entity work.mbr_sx(rtl) port map (
    mbr_i => dmem_out,
    sx_o  => mem_sx);

  register_file_inst : entity work.register_file(rtl) port map (
    rd_clk_i       => rd_clk,
    reset_i        => reset,
    dest_reg_i     => insn(11 downto 7),
    reg_sel_1_i    => insn(19 downto 15),
    reg_sel_2_i    => insn(24 downto 20),
    dest_reg_val_i => rd_val,
    reg_val_1_o    => rs1_val,
    reg_val_2_o    => rs2_val);

  with draddr_sel select draddr <=
    pc              when '1',
    alu             when '0',
    (others => 'X') when others;

  with iraddr_sel select iraddr <=
    pc              when '1',
    alu             when '0',
    (others => 'X') when others;

  with waddr_sel select waddr <=
    pc              when '1',
    alu             when '0',
    (others => 'X') when others;

  with rd_sel select rd_val <=
    mem_sx          when "11",
    (others => 'X') when "10",          -- could be where our RNG is gonna be
    alu             when "01",
    pc_alu          when "00",
    (others => 'X') when others;

  -- Branch to the same instruction (infinite loop) to signal being "done"
  with insn(6 downto 2) select done <=
    nor(imm_ex & pc_alu_sel & pc_next_sel) when OPCODE_BRANCH,
    '0'                                    when others;

  insn_register : process(reset, ir_clk, mem_write_en)
    use std.textio.all;
    variable l : line;
  begin
    if reset = '0' then
      insn <= (others => '0');
    elsif rising_edge(ir_clk) and mem_write_en = '0' then
      insn <= imem_out;
    end if;
  end process insn_register;

  print_reg : process(ir_clk)
    use std.textio.all;
    variable l : line;
  begin
    if rising_edge(ir_clk) then
      write(l, string'("dmem_out: "));
      write(l, to_hstring(dmem_out));
      write(l, string'(" imem_out: "));
      write(l, to_hstring(imem_out));
      writeline(output, l);
    end if;
  end process print_reg;
end rtl;
