rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
VHDL_SRC := $(call rwildcard,core,*.vhd)
VHDL_TESTS := $(call rwildcard,test,*.vhd)

FMT_SRC := $(patsubst %, fmt-%,$(VHDL_SRC) $(VHDL_TESTS))

clean:
	rm -fv **/*~

%_tb: test/%_tb.vhd core/%.vhd
	ghdl -c --std=08 $^ -r $@

alu_control_tb: test/alu_control_tb.vhd \
	core/alu_control.vhd \
	core/imm_sx.vhd \
	core/alu.vhd \
	core/program_counter.vhd \
	core/control_fsm.vhd

	ghdl -c --std=08 $^ -r $@

memory_tb: test/memory_tb.vhd \
	core/memory.vhd \
	core/mem.vhd \
	core/mbr_sx.vhd \
	core/register_file.vhd

	ghdl -c --std=08 $^ -r $@

fmt: $(FMT_SRC)

fmt-core/%.vhd: core/%.vhd
	@echo FORMAT $<
	@emacs -batch $< -f vhdl-beautify-buffer -f save-buffer 2>/dev/null

fmt-test/%.vhd: test/%.vhd
	@echo FORMAT $<
	@emacs -batch $< -f vhdl-beautify-buffer -f save-buffer 2>/dev/null

.PHONY: clean
