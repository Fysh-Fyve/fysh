rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

RTL_DIR := rtl
SRC_DIR := $(RTL_DIR)/core
TEST_DIR := $(RTL_DIR)/test

VHDL_SRC := $(call rwildcard,$(SRC_DIR),*.vhd)
VHDL_TEST_SRC := $(call rwildcard,$(TEST_DIR),*.vhd)
VHDL_TEST_BENCHES := $(patsubst $(TEST_DIR)/%.vhd, %, $(VHDL_TEST_SRC))

FMT_SRC := $(patsubst %, fmt-%,$(VHDL_SRC) $(VHDL_TEST_SRC))

GHDL_FLAGS := compile --std=08
# GHDL_FLAGS += -frelaxed
# RUN_FLAGS := --assert-level=warning # If you wanna be super strict

test: $(VHDL_TEST_BENCHES)

clean:
	rm -fv **/*~

%_tb: $(TEST_DIR)/%_tb.vhd $(SRC_DIR)/%.vhd
	@echo -----------------------------------------------------------------
	@echo TEST $@
	@ghdl $(GHDL_FLAGS) $^ -r $@ $(RUN_FLAGS)

_ALU := alu \
	fysh_pkg \

ALU := $(patsubst %, $(SRC_DIR)/%.vhd, $(_ALU))

_ALU_CONTROL := alu_control \
		imm_sx \
		program_counter \
		control_fsm \

ALU_CONTROL := $(patsubst %, $(SRC_DIR)/%.vhd, $(_ALU_CONTROL)) \
	$(ALU) \

alu_tb: $(TEST_DIR)/alu_tb.vhd $(ALU)
	@echo -----------------------------------------------------------------
	@echo TEST $@
	@ghdl $(GHDL_FLAGS) $^ -r $@ $(RUN_FLAGS)


alu_control_tb: $(TEST_DIR)/alu_control_tb.vhd $(ALU_CONTROL)
	@echo -----------------------------------------------------------------
	@echo TEST $@
	@ghdl $(GHDL_FLAGS) $^ -r $@ $(RUN_FLAGS)

_MEM := mem \
	fysh_pkg \

MEM := $(patsubst %, $(SRC_DIR)/%.vhd, $(_MEM))

mem_tb: $(TEST_DIR)/mem_tb.vhd $(MEM)
	@echo -----------------------------------------------------------------
	@echo TEST $@
	@ghdl $(GHDL_FLAGS) $^ -r $@ $(RUN_FLAGS)

_MEMORY := memory \
	   $(_MEM) \
	   phy_map \
	   mbr_sx \
	   register_file \

MEMORY := $(patsubst %, $(SRC_DIR)/%.vhd, $(_MEMORY))

memory_tb: $(TEST_DIR)/memory_tb.vhd $(MEMORY)
	@echo -----------------------------------------------------------------
	@echo TEST $@
	@ghdl $(GHDL_FLAGS) $^ -r $@ $(RUN_FLAGS)

topmodule_tb: $(TEST_DIR)/topmodule_tb.vhd \
	$(SRC_DIR)/topmodule.vhd \
	$(ALU_CONTROL) $(MEMORY)
	@echo -----------------------------------------------------------------
	@echo TEST $@
	@ghdl $(GHDL_FLAGS) $^ -r $@ $(RUN_FLAGS)

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

.PHONY: clean fmt test tcl clean-project
