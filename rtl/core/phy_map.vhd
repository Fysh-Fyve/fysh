--! \file phy_map.vhd
--! \author Charles Ancheta
--! @cond Doxygen_Suppress
library ieee;
use ieee.std_logic_1164.all;
use work.fysh_fyve.ROM_ADDR_W;
use work.rom.rom_arr;
--! @endcond


--! Creates physical maps to memory\n
--! 0x00000000 - 0x0000FFFF (ROM)\n
--! 0x00010000 - 0x0003FFFF (RAM)\n
--! 0xDEADBEE8 - 0xDEADBEEB (GPIO Pin mode)\n
--! 0xDEADBEEC - 0xDEADBEEF (GPIO)\n
entity phy_map is
  generic (VERBOSE : boolean := false);
  port (
    clk_i      : in std_ulogic;         --! Clock signal
    write_en_i : in std_ulogic;         --! Write enable

    iraddr_i : in  std_ulogic_vector (31 downto 0);  --! Instruction Read Address
    draddr_i : in  std_ulogic_vector (31 downto 0);  --! Data Read Address
    waddr_i  : in  std_ulogic_vector (31 downto 0);  --! Write Address
    d_i      : in  std_ulogic_vector (31 downto 0);  --! Data Input
    d_o      : out std_ulogic_vector (31 downto 0);  --! Data Output
    i_o      : out std_ulogic_vector (31 downto 0);  --! Instruction Output
    gpio     : out std_ulogic_vector (31 downto 0));  --! GPIO Pins

end phy_map;

architecture rtl of phy_map is
  --! Bit used for muxing/demuxing the two memory blocks.
  --! Maybe we should split them up more?
  constant MEM_SPLIT : integer := 17;

  signal ram_write_en       : std_ulogic;
  signal gpio_write_en      : std_ulogic;
  signal gpio_mode_write_en : std_ulogic;

  signal gpio_out : std_ulogic_vector (31 downto 0);
  signal mode_out : std_ulogic_vector (31 downto 0);
  signal dram_out : std_ulogic_vector (31 downto 0);
  signal drom_out : std_ulogic_vector (31 downto 0);
  signal irom_out : std_ulogic_vector (31 downto 0);

  signal rom_data_in : std_ulogic_vector (31 downto 0);

  signal gpio_addr_start : std_ulogic;

  signal le_data_in   : std_ulogic_vector (31 downto 0);
  signal le_idata_out : std_ulogic_vector (31 downto 0);
  signal le_ddata_out : std_ulogic_vector (31 downto 0);

  type mem_sel_t is (gpio_sel, gpio_mode_sel, rom_sel, ram_sel);
  signal imem_sel, dmem_sel, wmem_sel    : mem_sel_t;
  signal wgpio_sel, dgpio_sel, igpio_sel : mem_sel_t;

  procedure write_mem_sel (l : inout std.textio.line; sel : in mem_sel_t) is
    use std.textio.all;
  begin
    case sel is
      when gpio_sel      => write(l, string'("gpio"));
      when gpio_mode_sel => write(l, string'("mode"));
      when rom_sel       => write(l, string'("rom "));
      when ram_sel       => write(l, string'("ram "));
    end case;
  end write_mem_sel;

begin
  d_o <= le_ddata_out(7 downto 0)
         & le_ddata_out(15 downto 8)
         & le_ddata_out(23 downto 16)
         & le_ddata_out(31 downto 24);

  i_o <= le_idata_out(7 downto 0)
         & le_idata_out(15 downto 8)
         & le_idata_out(23 downto 16)
         & le_idata_out(31 downto 24);

  le_data_in <= d_i(7 downto 0)
                & d_i(15 downto 8)
                & d_i(23 downto 16)
                & d_i(31 downto 24);

  print_write : process(clk_i, write_en_i)
    use std.textio.all;
    variable l : line;
  begin
    if rising_edge(clk_i) and write_en_i = '1' then
      write(l, string'("w_adrr: "));
      write(l, to_hstring(waddr_i));
      write(l, string'(", mem sel: "));
      write_mem_sel(l, wmem_sel);
      writeline(output, l);
    end if;
  end process print_write;

  ram_write_en       <= write_en_i and '1' when (wmem_sel = ram_sel)       else '0';
  gpio_write_en      <= write_en_i and '1' when (wmem_sel = gpio_sel)      else '0';
  gpio_mode_write_en <= write_en_i and '1' when (wmem_sel = gpio_mode_sel) else '0';

  with imem_sel select le_idata_out <=
    gpio_out when gpio_sel,
    dram_out when ram_sel,
    irom_out when rom_sel,
    mode_out when gpio_mode_sel;

  with dmem_sel select le_ddata_out <=
    gpio_out when gpio_sel,
    dram_out when ram_sel,
    drom_out when rom_sel,
    mode_out when gpio_mode_sel;

  with waddr_i(31 downto 16) select wmem_sel <=
    wgpio_sel when x"DEAD",
    rom_sel   when x"0000",
    ram_sel   when others;

  with draddr_i(31 downto 16) select dmem_sel <=
    dgpio_sel when x"DEAD",
    rom_sel   when x"0000",
    ram_sel   when others;

  with iraddr_i(31 downto 16) select imem_sel <=
    igpio_sel when x"DEAD",
    rom_sel   when x"0000",
    ram_sel   when others;

  -- This only works for aligned access
  -- TODO: Support unaligned access
  with waddr_i(15 downto 0) select wgpio_sel <=
    gpio_mode_sel when x"BEE8", gpio_sel when others;
  with draddr_i(15 downto 0) select dgpio_sel <=
    gpio_mode_sel when x"BEE8", gpio_sel when others;
  with iraddr_i(15 downto 0) select igpio_sel <=
    gpio_mode_sel when x"BEE8", gpio_sel when others;

  gpio_inst : entity work.gpio_pins(rtl)
    generic map(VERBOSE => VERBOSE)
    port map (
      clk_i           => clk_i,
      gp_io           => gpio,
      write_en_i      => gpio_write_en,
      mode_write_en_i => gpio_mode_write_en,
      pin_mode_i      => le_data_in,
      pin_write_i     => le_data_in,
      pin_read_o      => gpio_out,
      mode_o          => mode_out);

  rom_inst : entity work.brom(rtl)
    generic map (
      DATA   => rom_arr,
      ADDR_W => ROM_ADDR_W)
    port map (
      clk_i        => clk_i,
      iread_addr_i => iraddr_i(ROM_ADDR_W+1 downto 2),
      dread_addr_i => draddr_i(ROM_ADDR_W+1 downto 2),
      d_o          => drom_out,
      i_o          => irom_out);

  ram_inst : entity work.bram(rtl)
    port map (
      clk_i        => clk_i,
      read_addr_i  => draddr_i(MEM_SPLIT-1 downto 2),
      write_addr_i => waddr_i(MEM_SPLIT-1 downto 2),
      write_en_i   => ram_write_en,
      d_i          => le_data_in,
      d_o          => dram_out);
end rtl;
