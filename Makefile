rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) \
	  $(filter $(subst *,%,$2),$d))

FYSH := $(shell command -v fysh-sea 2> /dev/null)
RTL_DIR := rtl
SRC_DIR := $(RTL_DIR)/core
TEST_DIR := $(RTL_DIR)/test

VHDL_SRC := $(call rwildcard,$(SRC_DIR),*.vhd)
VHDL_TEST_SRC := $(call rwildcard,$(TEST_DIR),*.vhd)
VHDL_TEST_BENCHES := $(patsubst $(TEST_DIR)/%.vhd, %, $(VHDL_TEST_SRC))

ASM_SRC := $(call rwildcard,asm,*.s)
ASM_HEX := $(patsubst %.s,%.hex,$(ASM_SRC))

FMT_SRC := $(patsubst %, fmt-%,$(VHDL_SRC) $(VHDL_TEST_SRC))

export GHDL_FLAGS := compile --std=08
# GHDL_FLAGS += -frelaxed
# If you wanna silence annoying errors
export RUN_FLAGS := --ieee-asserts=disable
ifdef VERBOSE
RUN_FLAGS += -gVERBOSE=$(VERBOSE)
endif
ifdef WAVE
RUN_FLAGS += --wave=wave.ghw
endif
# export RUN_FLAGS := --assert-level=warning # If you wanna be super strict

test: $(VHDL_TEST_BENCHES)

wave:
	WAVE=1 $(MAKE) topmodule_tb

clean:
	rm -fv **/*~ asm/*.hex asm/*.elf asm/*.o sw/*.o fysh/*.o fysh/*.hex

hex: $(ASM_HEX)

rom: rtl/core/rom_pkg.vhd

rtl/core/rom_pkg.vhd: asm/example.hex \
	build/fyve-rom \
	scripts/rom_pkg.part1.vhd \
	scripts/rom_pkg.part2.vhd
	./scripts/make_rom.sh $<

%.dump: asm/%.elf
	llvm-objdump -D --section=.text --section=.sdata --arch-name=riscv32 $<

%.dump: sw/%.elf
	llvm-objdump -D --section=.text --section=.sdata --arch-name=riscv32 $<

%.dump: fysh/%.elf
	llvm-objdump -D --section=.text --section=.sdata --arch-name=riscv32 $<

%.rom: asm/%.hex
	./scripts/make_rom.sh $<

%.rom: fysh/%.hex
	./scripts/make_rom.sh $<

.PRECIOUS: %.hex
%.hex: %.elf
	llvm-objcopy -O binary $< $@

%.elf: sw/fysh-fyve.ld sw/boot.o sw/gpio.o sw/mulsi3.o %.o
	clang --target=riscv32 -march=rv32i -nostdlib -T $^ -o $@

%.o: %.c
	clang -c $< -O3 --target=riscv32 -march=rv32i -nostdlib -o $@

%.s: %.fysh
	$(FYSH) $< | llc -O3 -march=riscv32 -o $@

%.s: %.c
	clang -S $< -O3 --target=riscv32 -march=rv32i -nostdlib -o $@

%.o: %.s
	clang -c $< -O3 --target=riscv32 -march=rv32i -nostdlib -o $@

build/fyve-%: scripts/%.cc | build
	cd build && cmake ../scripts && make

build:
	mkdir -p $@

%_tb: $(TEST_DIR)/%_tb.vhd $(SRC_DIR)/%.vhd
	@TB="$@" ./scripts/run_test.sh $^

_CONTROLLER := control_fsm \
	       fysh_fyve_pkg \

CONTROLLER := $(patsubst %, $(SRC_DIR)/%.vhd, $(_CONTROLLER))

control_fsm_tb: $(TEST_DIR)/control_fsm_tb.vhd $(CONTROLLER)
	@TB="$@" ./scripts/run_test.sh $^

_ALU := alu fysh_fyve_pkg
_IMM_SX := imm_sx fysh_fyve_pkg
_ALU_CONTROL := imm_sx \
		program_counter \
		control_fsm \
		clk_divider
_MEM := mem \
	brom \
	bram \
	rom_pkg \
	fysh_fyve_pkg
_MEMORY := $(_MEM) \
	   phy_map \
	   gpio_pins \
	   counter \
	   mbr_sx \
	   register_file \
	   grilled_fysh

ALU := $(patsubst %, $(SRC_DIR)/%.vhd, $(_ALU))
alu_tb: $(TEST_DIR)/alu_tb.vhd $(ALU)
	@TB="$@" ./scripts/run_test.sh $^

IMM_SX := $(patsubst %, $(SRC_DIR)/%.vhd, $(_IMM_SX))
imm_sx_tb: $(TEST_DIR)/imm_sx_tb.vhd $(IMM_SX)
	@TB="$@" ./scripts/run_test.sh $^

MEM := $(patsubst %, $(SRC_DIR)/%.vhd, $(_MEM))
mem_tb: $(TEST_DIR)/mem_tb.vhd $(MEM)
	@TB="$@" ./scripts/run_test.sh $^

MEMORY := $(patsubst %, $(SRC_DIR)/%.vhd, $(_MEMORY))
phy_map_tb: $(TEST_DIR)/phy_map_tb.vhd $(MEMORY)
	@TB="$@" ./scripts/run_test.sh $^

ALU_CONTROL := $(patsubst %, $(SRC_DIR)/%.vhd, $(_ALU_CONTROL)) $(ALU)
topmodule_tb: $(TEST_DIR)/topmodule_tb.vhd \
	$(SRC_DIR)/topmodule.vhd \
	$(ALU_CONTROL) $(MEMORY)
	@TB="$@" ./scripts/run_test.sh $^

fmt: $(FMT_SRC)

fmt-$(RTL_DIR)/%.vhd: $(RTL_DIR)/%.vhd
	@echo FORMAT $<
	@emacs -batch $< -f vhdl-beautify-buffer -f save-buffer 2>/dev/null

VIVADO_PROJECT_DIR := proj
VIVADO_PROJECT_NAME := fysh-fyve
VIVADO_PROJECT_FILE := $(VIVADO_PROJECT_DIR)/$(VIVADO_PROJECT_NAME).xpr

tcl: $(VIVADO_PROJECT_FILE)
	vivado -mode tcl $<

$(VIVADO_PROJECT_FILE):
	vivado -mode batch -source fysh-fyve.tcl

clean-project:
	rm -rf $(VIVADO_PROJECT_DIR)

.PHONY: clean fmt test tcl clean-project rom hex
