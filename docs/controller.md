# Controller Outputs

```
rd_sel_o  : out std_ulogic_vector (1 downto 0)

sub_sra_o      : out std_ulogic
addr_sel_o     : out std_ulogic
alu_a_sel_o    : out std_ulogic
alu_b_sel_o    : out std_ulogic
mem_write_en_o : out std_ulogic
rd_clk_o       : out std_ulogic
pc_clk_o       : out std_ulogic
ir_clk_o       : out std_ulogic
pc_alu_sel_o   : out std_ulogic
pc_next_sel_o  : out std_ulogic
done_o         : out std_logic
```

| Instruction | rd[1:0] | sub_sra | addr | alu_a | alu_b | mem_write_en | rd_clk | pc_clk | ir_clk | pc_alu | pc_next |
| ----------- | ------- | ------- | ---- | ----- | ----- | ------------ | ------ | ------ | ------ | ------ | ------- |
| lui         | 01      | 0       | 1    | [1]   | 1     | 0            | dr     | dr     | dr     | 1      | 0       |
| auipc       | 01      | 0       | 1    | 1     | 1     | 0            | dr     | dr     | dr     | 1      | 0       |
| addi        | 01      | 0       | 1    | 0     | 1     | 0            | dr     | dr     | dr     | 1      | 0       |
| sw          | XX      | 0       | 0    | 0     | 0     | 1            | no     | dr     | dr     | 1      | 0       |

| A     | B                  | A ^ B    |
| ----- | ------------------ | -------- |
| lui   | auipc              | bit 5    |
| auipc | register-immediate | bit 2    |
| lui   | register-immediate | bit 2, 5 |
| sw    | register-immediate | bit 2, 5 |

0100011
0010011

[^1] This somehow has to be pointing to 0! how? and the op bits should be add!
