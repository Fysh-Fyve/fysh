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
--! 0xDEADBEEC - 0xDEADBEEF (GPIO)\n
entity phy_map is
  port (
    clk_i      : in std_ulogic;         --! Clock signal
    write_en_i : in std_ulogic;         --! Write enable

    iraddr_i : in    std_ulogic_vector (31 downto 0);  --! Instruction Read Address
    draddr_i : in    std_ulogic_vector (31 downto 0);  --! Data Read Address
    waddr_i  : in    std_ulogic_vector (31 downto 0);  --! Write Address
    d_i      : in    std_ulogic_vector (31 downto 0);  --! Data Input
    d_o      : out   std_ulogic_vector (31 downto 0);  --! Data Output
    i_o      : out   std_ulogic_vector (31 downto 0);  --! Instruction Output
    -- TODO: GPIO PIN Mode???
    gpio     : inout std_ulogic_vector (31 downto 0));  --! GPIO Pins

end phy_map;

architecture rtl of phy_map is
  --! Bit used for muxing/demuxing the two memory blocks.
  --! Maybe we should split them up more?
  constant MEM_SPLIT : integer := 17;

  signal ram_write_en  : std_ulogic;
  signal gpio_write_en : std_ulogic;

  signal gpio_out : std_ulogic_vector (31 downto 0);
  signal dram_out : std_ulogic_vector (31 downto 0);
  signal drom_out : std_ulogic_vector (31 downto 0);
  signal irom_out : std_ulogic_vector (31 downto 0);

  signal rom_data_in : std_ulogic_vector (31 downto 0);

  signal gpio_addr_start : std_ulogic;

  signal le_data_in   : std_ulogic_vector (31 downto 0);
  signal le_idata_out : std_ulogic_vector (31 downto 0);
  signal le_ddata_out : std_ulogic_vector (31 downto 0);

  type mem_sel_t is (gpio_sel, rom_sel, ram_sel);
  signal imem_sel, dmem_sel, wmem_sel : mem_sel_t;
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

  ram_write_en  <= write_en_i and '1' when (wmem_sel = ram_sel)  else '0';
  gpio_write_en <= write_en_i and '1' when (wmem_sel = gpio_sel) else '0';

  gpio_clk : process(clk_i, gpio)
  begin
    if rising_edge(clk_i) then
      if gpio_write_en = '1' then
        gpio <= le_data_in;
      end if;
    end if;
    gpio_out <= gpio;
  end process gpio_clk;

  with imem_sel select le_idata_out <=
    gpio_out when gpio_sel,
    dram_out when ram_sel,
    irom_out when rom_sel;

  with dmem_sel select le_ddata_out <=
    gpio_out when gpio_sel,
    dram_out when ram_sel,
    drom_out when rom_sel;

  with waddr_i(31 downto 16) select wmem_sel <=
    gpio_sel when x"DEAD",
    rom_sel  when x"0000",
    ram_sel  when others;

  with draddr_i(31 downto 16) select dmem_sel <=
    gpio_sel when x"DEAD",
    rom_sel  when x"0000",
    ram_sel  when others;

  with iraddr_i(31 downto 16) select imem_sel <=
    gpio_sel when x"DEAD",
    rom_sel  when x"0000",
    ram_sel  when others;

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
