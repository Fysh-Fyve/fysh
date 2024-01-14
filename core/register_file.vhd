--! \file register_file.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--! @endcond

entity register_file is
  port (
    rd_clk_i, reset_i    : in  std_ulogic;
    rd_i, rs1_i, rs2_i   : in  std_ulogic_vector (4 downto 0);
    rd_val_i             : in  std_ulogic_vector (31 downto 0);
    rs1_val_o, rs2_val_o : out std_ulogic_vector (31 downto 0));
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
        if (i = to_integer(unsigned(rd_i))) then
          reg_file(i) <= rd_val_i;
        end if;
      end if;
    end process register_write;
  end generate;

  register_read : process(rd_clk_i)
  begin
    if rising_edge(rd_clk_i) then
      rs1_val_o <= reg_file(to_integer(unsigned(rs1_i)));
      rs2_val_o <= reg_file(to_integer(unsigned(rs2_i)));
    end if;
  end process register_read;
end Behavioral;
