library ieee;
use ieee.std_logic_1164.all;

entity register_file_tb is
end register_file_tb;

architecture Behavioral of register_file_tb is
  signal rd_clk     : std_ulogic                     := '0';
  signal loop_count : integer                        := 0;
  signal reset      : std_ulogic;
  signal rd         : std_ulogic_vector (4 downto 0) := (others => '0');  -- Register Destination
  signal rs1        : std_ulogic_vector (4 downto 0) := (others => '0');  -- Register Source 1
  signal rs2        : std_ulogic_vector (4 downto 0) := (others => '0');  -- Register Source 2

  signal rd_val  : std_ulogic_vector (31 downto 0);
  signal rs1_val : std_ulogic_vector (31 downto 0) := (others => '0');
  signal rs2_val : std_ulogic_vector (31 downto 0) := (others => '0');

  component register_file is
    port (
      rd_clk : in std_ulogic;
      reset  : in std_ulogic;

      rd  : in std_ulogic_vector (4 downto 0);  -- Register Destination
      rs1 : in std_ulogic_vector (4 downto 0);  -- Register Source 1
      rs2 : in std_ulogic_vector (4 downto 0);  -- Register Source 2

      rd_val  : in  std_ulogic_vector (31 downto 0);
      rs1_val : out std_ulogic_vector (31 downto 0);
      rs2_val : out std_ulogic_vector (31 downto 0));
  end component;
begin
  reg_file : register_file port map(
    rd_clk  => rd_clk,
    reset   => reset,
    rd      => rd,
    rs1     => rs1,
    rs2     => rs2,
    rd_val  => rd_val,
    rs1_val => rs1_val,
    rs2_val => rs2_val);

  clock : process
  begin
    rd_clk <= '0';
    wait for 1 fs;
    for i in 0 to 31 loop
      rd_clk     <= '1';
      loop_count <= i;
      wait for 5 ns;
      rd_clk     <= '0';
      wait for 5 ns;
    end loop;
    wait;
  end process;

  reg_file_testing : process
    use ieee.numeric_std.all;
  begin
    reset  <= '0';
    wait for 1 fs;
    reset  <= '1';
    rd     <= (others => '0');
    rd_val <= (others => '0');
    rs1    <= (others => '0');
    rs2    <= (others => '0');
    wait for 1 fs;

    for i in 0 to 31 loop
      rd <= std_ulogic_vector(to_unsigned(i, 5));
      wait for 5 ns;
      if i > 2 then
        rs1 <= std_ulogic_vector(to_unsigned(i-1, 5));
        rs2 <= std_ulogic_vector(to_unsigned(i-2, 5));
      end if;
      rd_val <= std_ulogic_vector(to_unsigned(i + 1, 32));
      wait for 5 ns;
    end loop;

    wait;
  end process;

  print_out : process (rd_clk)
    use std.textio.all;
    variable my_line : line;
  begin
    write(my_line, rd_clk, left, 5);
    write(my_line, loop_count, left, 5);
    write(my_line, to_hstring(rs1_val), left, 10);
    write(my_line, to_hstring(rs2_val), left, 10);
    writeline(output, my_line);
  end process;
end Behavioral;
