all: test/doctest.h build/Makefile
	cd build && $(MAKE) -s

build/Makefile:
	cd build && cmake ..

test/doctest.h:
	wget -O $@ https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h

build/compile_commands.json: build
	cd build && cmake ..

build:
	mkdir -p $@

test: all
	./build/test/tests

run: all
	./build/fysh

clean:
	cd build && $(MAKE) -s clean

.PHONY: clean run test all
