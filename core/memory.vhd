--! \file memory.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! A higher-level module which contains the Memory, Register File, and Instruction Register.\n

entity memory is
  port (
    --! Clock signal for the Register File.
    rd_clk_i   : in std_ulogic;
    --! Clock signal for the Memory.
    mem_clk_i  : in std_ulogic;
    --! Clock signal for the Instruction Register.
    insn_clk_i : in std_ulogic;
    --! Flag to select the address either from the ALU or the PC.
    addr_sel_i : in std_ulogic;
    --! The reset signal.
    reset_i    : in std_ulogic;
    sx_size_i  : in std_ulogic_vector (2 downto 0);
    --! Flags to select the value to be written to the Register File.
    rd_sel_i   : in std_ulogic_vector (1 downto 0);
    --! Output of the ALU.
    alu_i      : in std_ulogic_vector (31 downto 0);
    --! Output of the Program Counter.
    pc_i       : in std_ulogic_vector (31 downto 0);
    --! Output of the Program Counter's ALU.
    pc_alu_i   : in std_ulogic_vector (31 downto 0);

    --! Read 32-bit instruction from memory.
    insn_o          : out std_ulogic_vector (31 downto 0);
    --! First selected value from the Register File.
    reg_sel_1_val_o : out std_ulogic_vector (31 downto 0);
    --! Second selected value from the Register File.
    reg_sel_2_val_o : out std_ulogic_vector (31 downto 0));
end memory;

architecture Behavioral of memory is
  component mem is port (
    d_i, read_addr_i, write_addr_i : in  std_ulogic_vector (31 downto 0);
    write_en_i                     : in  std_ulogic;
    d_o                            : out std_ulogic_vector (31 downto 0));
  end component;

  component mbr_sx is port (
    mbr_i  : in  std_ulogic_vector (31 downto 0);
    size_i : in  std_ulogic_vector (2 downto 0);
    sx_o   : out std_ulogic_vector (31 downto 0));
  end component;

  component register_file is
    port (
      rd_clk_i : in std_ulogic;
      reset_i  : in std_ulogic;

      dest_reg_i  : in std_ulogic_vector (4 downto 0);  -- Register Destination
      reg_sel_1_i : in std_ulogic_vector (4 downto 0);  -- Register Source 1
      reg_sel_2_i : in std_ulogic_vector (4 downto 0);  -- Register Source 2

      dest_reg_val_i  : in  std_ulogic_vector (31 downto 0);
      reg_sel_1_val_o : out std_ulogic_vector (31 downto 0);
      reg_sel_2_val_o : out std_ulogic_vector (31 downto 0));
  end component;

  signal rd_val                : std_ulogic_vector (31 downto 0);
  signal addr, mem_out, mem_sx : std_ulogic_vector (31 downto 0);

begin
  mem_inst : component mem port map (
    read_addr_i  => addr,
    write_addr_i => addr,
    write_en_i   => mem_clk_i,
    d_i          => reg_sel_2_val_o,
    d_o          => mem_out);

  mbr_sx_inst : component mbr_sx port map (
    mbr_i  => mem_out,
    size_i => sx_size_i,
    sx_o   => mem_sx);

  register_file_inst : component register_file port map (
    rd_clk_i        => rd_clk_i,
    reset_i         => reset_i,
    dest_reg_i      => insn_o(24 downto 20),
    reg_sel_1_i     => insn_o(19 downto 15),
    reg_sel_2_i     => insn_o(24 downto 20),
    dest_reg_val_i  => rd_val,
    reg_sel_1_val_o => reg_sel_1_val_o,
    reg_sel_2_val_o => reg_sel_2_val_o);

  with addr_sel_i select addr <=
    pc_i            when '1',
    alu_i           when '0',
    (others => 'X') when others;

  with rd_sel_i select rd_val <=
    mem_sx          when "11",
    (others => 'X') when "10",
    alu_i           when "01",
    pc_alu_i        when "00",
    (others => 'X') when others;

  insn_register : process(reset_i, insn_clk_i)
  begin
    if (reset_i = '0') then
      insn_o <= (others => '0');
    elsif rising_edge(insn_clk_i) then
      insn_o <= mem_out;
    end if;
  end process insn_register;
end Behavioral;
