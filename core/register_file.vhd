--! \file register_file.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--! @endcond

--! Register File. Contains the 32-bit registers of the CPU.\n

--! The register file has one 32-bit input port and two 32-bit output ports.\n
--! `reg_sel_1_i` and `rs_2_i` selects the two values to be output from the registers
--! while `dest_reg_i` determines the register to be written to by `dest_reg_val_i`.
entity register_file is
  port (
    --! Register File Clock Signal.
    rd_clk_i        : in  std_ulogic;
    --! Reset Signal.
    reset_i         : in  std_ulogic;
    --! Destination Register.
    dest_reg_i      : in  std_ulogic_vector (4 downto 0);
    --! Register Select 1.
    reg_sel_1_i     : in  std_ulogic_vector (4 downto 0);
    --! Register Select 2.
    reg_sel_2_i     : in  std_ulogic_vector (4 downto 0);
    --! Value to write to the Destination Register.
    dest_reg_val_i  : in  std_ulogic_vector (31 downto 0);
    --! Value of Register Select 1.
    reg_sel_1_val_o : out std_ulogic_vector (31 downto 0);
    --! Value of Register Select 2 Value.
    reg_sel_2_val_o : out std_ulogic_vector (31 downto 0));
end register_file;

architecture Behavioral of register_file is
  type reg_file_t is array (31 downto 0) of std_ulogic_vector(31 downto 0);  -- 32 32-bit registers
  signal reg_file : reg_file_t;
begin
  registers_g :
  for i in 0 to 31 generate
    register_write : process(reset_i, rd_clk_i)
    begin
      if (reset_i = '0') then
        reg_file(i) <= (others => '0');
      elsif rising_edge(rd_clk_i) then
        if (i = to_integer(unsigned(dest_reg_i))) then
          reg_file(i) <= dest_reg_val_i;
        end if;
      end if;
    end process register_write;
  end generate;

  register_read : process(rd_clk_i)
  begin
    if rising_edge(rd_clk_i) then
      reg_sel_1_val_o <= reg_file(to_integer(unsigned(reg_sel_1_i)));
      reg_sel_2_val_o <= reg_file(to_integer(unsigned(reg_sel_2_i)));
    end if;
  end process register_read;
end Behavioral;
