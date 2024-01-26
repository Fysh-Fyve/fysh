set_property -dict {PACKAGE_PIN K17 IOSTANDARD LVCMOS33} [get_ports { clk }];
create_clock -period 8.000 -name sys_clk_pin -waveform {0.000 4.000} -add [get_ports { clk }];

# Pmod Header JC
set_property -dict { PACKAGE_PIN V15   IOSTANDARD LVCMOS33     } [get_ports { alu_o[0] }];
set_property -dict { PACKAGE_PIN W15   IOSTANDARD LVCMOS33     } [get_ports { alu_o[1] }];
set_property -dict { PACKAGE_PIN T11   IOSTANDARD LVCMOS33     } [get_ports { alu_o[2] }];
set_property -dict { PACKAGE_PIN T10   IOSTANDARD LVCMOS33     } [get_ports { alu_o[3] }];
set_property -dict { PACKAGE_PIN W14   IOSTANDARD LVCMOS33     } [get_ports { alu_o[4] }];
set_property -dict { PACKAGE_PIN Y14   IOSTANDARD LVCMOS33     } [get_ports { alu_o[5] }];
set_property -dict { PACKAGE_PIN T12   IOSTANDARD LVCMOS33     } [get_ports { alu_o[6] }];
set_property -dict { PACKAGE_PIN U12   IOSTANDARD LVCMOS33     } [get_ports { alu_o[7] }];
