all: test/doctest.h | build
	cd build && $(MAKE) -s

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
