%_tb: test/%_tb.vhd core/%.vhd
	ghdl -c --std=08 $^ -r $@

clean:
	rm -fv **/*~
.PHONY: clean
