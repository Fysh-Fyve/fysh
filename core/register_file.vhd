library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity register_file is
  port (
    rd_clk : in std_ulogic;
    reset  : in std_ulogic;

    rd  : in std_ulogic_vector (4 downto 0);  -- Register Destination
    rs1 : in std_ulogic_vector (4 downto 0);  -- Register Source 1
    rs2 : in std_ulogic_vector (4 downto 0);  -- Register Source 2

    rd_val  : in  std_ulogic_vector (31 downto 0);
    rs1_val : out std_ulogic_vector (31 downto 0);
    rs2_val : out std_ulogic_vector (31 downto 0));
end register_file;

architecture Behavioral of register_file is
  type reg_file_t is array (31 downto 0) of std_ulogic_vector(31 downto 0);  -- 32 32-bit registers
  signal reg_file : reg_file_t;
begin
  reg_gen :
  for i in 0 to 31 generate
    register_write : process(reset, rd_clk)
    begin
      if (reset = '0') then
        reg_file(i) <= (others => '0');
      elsif rising_edge(rd_clk) then
        if (i = to_integer(unsigned(rd))) then
          reg_file(i) <= rd_val;
        end if;
      end if;
    end process register_write;

  end generate;

  register_read : process(rd_clk)
  begin
    if rising_edge(rd_clk) then
      rs1_val <= reg_file(to_integer(unsigned(rs1)));
      rs2_val <= reg_file(to_integer(unsigned(rs2)));
    end if;
  end process register_read;
end Behavioral;
