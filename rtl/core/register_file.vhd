--! \file register_file.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--! @endcond

--! Register File. Contains the 32-bit registers of the CPU.\n

--! The register file has one 32-bit input port and two 32-bit output ports.\n
--! `reg_sel_1_i` and `reg_sel_2_i` selects the two values to be output from the
--! registers while `dest_reg_i` determines the register to be written to by
--! `dest_reg_val_i`.
entity register_file is
  generic (VERBOSE : boolean := false);
  port (
    rd_clk_i       : in  std_ulogic;    --! Register File Clock Signal
    reset_i        : in  std_ulogic;    --! Reset Signal
    dest_reg_i     : in  std_ulogic_vector (4 downto 0);  --! Destination Register
    reg_sel_1_i    : in  std_ulogic_vector (4 downto 0) := (others => '0');  --! First Register Select
    reg_sel_2_i    : in  std_ulogic_vector (4 downto 0) := (others => '0');  --! Second Register Select
    dest_reg_val_i : in  std_ulogic_vector (31 downto 0);  --! Value to write to the Destination Register
    reg_val_1_o    : out std_ulogic_vector (31 downto 0);  --! Value of Register Select 1
    reg_val_2_o    : out std_ulogic_vector (31 downto 0));  --! Value of Register Select 2
end register_file;

architecture rtl of register_file is
  type reg_file_t is array (31 downto 0) of std_ulogic_vector(31 downto 0);  -- 32 32-bit registers
  signal reg_file : reg_file_t := (others => (31 downto 0 => '0'));
begin
  registers_g :
  for i in 1 to 31 generate
    register_write : process(reset_i, rd_clk_i)
      use std.textio.all;
      variable l : line;
    begin
      if reset_i = '1' then
        reg_file(i) <= (others => '0');
      elsif rising_edge(rd_clk_i) then
        if (i = to_integer(unsigned(dest_reg_i))) then
          if VERBOSE then
            write(l, string'("wrote value "));
            write(l, to_hstring(dest_reg_val_i));
            write(l, string'(" to register "));
            write(l, i);
            writeline(output, l);
          end if;
          reg_file(i) <= dest_reg_val_i;
        end if;
      end if;
    end process register_write;
  end generate;

  -- x0 is hardwired to zero
  -- https://five-embeddev.com/riscv-isa-manual/latest/rv32.html#gprs
  reg_file(0) <= (others => '0');

  -- Async! hell yeah I am not sure if this works
  register_read : process(reg_sel_1_i, reg_sel_2_i, rd_clk_i, reg_file)
  begin
    reg_val_1_o <= reg_file(to_integer(unsigned(reg_sel_1_i)));
    reg_val_2_o <= reg_file(to_integer(unsigned(reg_sel_2_i)));
  end process register_read;
end rtl;
