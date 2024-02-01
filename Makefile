NINJA := $(shell command -v ninja 2> /dev/null)

ifdef NINJA
BUILD ?= ninja
else
BUILD ?= $(MAKE) -s
endif

ifeq ($(BUILD), ninja)
CMAKE_FLAGS += -GNinja
endif

ifdef RELEASE
CMAKE_FLAGS += -DCMAKE_BUILD_TYPE=Release
endif


all: test/doctest.h build/compile_commands.json
	cd build && $(BUILD)

build/compile_commands.json: build
	cd build && cmake $(CMAKE_FLAGS) ..

test/doctest.h:
	wget -O $@ https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h

build:
	mkdir -p $@

test: all
	./build/test/tests

run: all
	./build/fysh

clean:
	cd build && $(BUILD) clean

.PHONY: clean run test all
