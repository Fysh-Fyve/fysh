rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
VHDL_SRC := $(call rwildcard,core,*.vhd)
VHDL_TESTS := $(call rwildcard,test,*.vhd)

FMT_SRC := $(patsubst %, fmt-%,$(VHDL_SRC) $(VHDL_TESTS))

%_tb: test/%_tb.vhd core/%.vhd
	ghdl -c --std=08 $^ -r $@

clean:
	rm -fv **/*~

fmt: $(FMT_SRC)

fmt-core/%.vhd: core/%.vhd
	@echo FORMAT $<
	@emacs -batch $< -f vhdl-beautify-buffer -f save-buffer 2>/dev/null

fmt-test/%.vhd: test/%.vhd
	@echo FORMAT $<
	@emacs -batch $< -f vhdl-beautify-buffer -f save-buffer 2>/dev/null

.PHONY: clean
