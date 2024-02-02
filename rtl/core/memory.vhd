--! \file memory.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
--! @endcond

--! A higher-level module which contains the Memory, Register File, and Instruction Register.\n

entity memory is
  port (
    clk_i      : in std_ulogic;
    rd_clk_i   : in std_ulogic;         --!  Register File clock signal
    write_en_i : in std_ulogic;         --! Memory clock signal
    insn_clk_i : in std_ulogic;         --! Instruction Register clock signal

    addr_sel_i   : in std_ulogic;       --! ALU & PC address select signal
    reset_i      : in std_ulogic;       --! Reset signal
    sx_size_i    : in std_ulogic_vector (2 downto 0);
    rd_sel_i     : in std_ulogic_vector (1 downto 0);  --! Register File write select
    alu_out_i    : in std_ulogic_vector (31 downto 0);  --! Output of the ALU.
    pc_out_i     : in std_ulogic_vector (31 downto 0);  --! Output of the Program Counter. (same as above)
    pc_alu_out_i : in std_ulogic_vector (31 downto 0);  --! Output of the Program Counter's ALU. (same as above)

    insn_o      : out   std_ulogic_vector (31 downto 0);  --! Instruction Register output.
    reg_val_1_o : out   std_ulogic_vector (31 downto 0);  --! First selected register value
    reg_val_2_o : out   std_ulogic_vector (31 downto 0);  --! Second selected register value
    gpio        : inout std_ulogic_vector (31 downto 0));  --! GPIO Pins
end memory;

architecture rtl of memory is
  signal rd_val, insn          : std_ulogic_vector (31 downto 0);
  signal addr, mem_out, mem_sx : std_ulogic_vector (31 downto 0);
  signal reg_val_1, reg_val_2  : std_ulogic_vector (31 downto 0);

begin
  mem_inst : entity work.phy_map(rtl) port map (
    clk_i      => clk_i,
    addr_i     => addr,
    write_en_i => write_en_i,
    d_i        => reg_val_2,
    d_o        => mem_out,
    gpio       => gpio
    );

  mbr_sx_inst : entity work.mbr_sx(rtl) port map (
    mbr_i  => mem_out,
    size_i => sx_size_i,
    sx_o   => mem_sx);

  register_file_inst : entity work.register_file(rtl) port map (
    rd_clk_i       => rd_clk_i,
    reset_i        => reset_i,
    dest_reg_i     => insn(24 downto 20),
    reg_sel_1_i    => insn(19 downto 15),
    reg_sel_2_i    => insn(24 downto 20),
    dest_reg_val_i => rd_val,
    reg_val_1_o    => reg_val_1,
    reg_val_2_o    => reg_val_2);

  reg_val_2_o <= reg_val_2;
  reg_val_1_o <= reg_val_1;
  insn_o      <= insn;

  with addr_sel_i select addr <=
    pc_out_i        when '1',
    alu_out_i       when '0',
    (others => 'X') when others;

  with rd_sel_i select rd_val <=
    mem_sx          when "11",
    (others => 'X') when "10",          -- could be where our RNG is gonna be
    alu_out_i       when "01",
    pc_alu_out_i    when "00",
    (others => 'X') when others;

  insn_register : process(reset_i, insn_clk_i)
  begin
    if (reset_i = '0') then
      insn <= (others => '0');
    elsif rising_edge(insn_clk_i) then
      insn <= mem_out;
    end if;
  end process insn_register;
end rtl;
