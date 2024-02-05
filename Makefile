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

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRC := $(call rwildcard,src,*.cc) \
       $(call rwildcard,src,*.h) \
       $(call rwildcard,test,*.cc) \
       $(call rwildcard,test,*.h) \
       $(call rwildcard,asm,*.cc) \
       $(call rwildcard,asm,*.h)

all: doctest/doctest.h build/compile_commands.json
	cd build && $(BUILD)

fmt: $(SRC)
	for i in $(SRC); do clang-format -i $$i; done

build/compile_commands.json: build
	cd build && cmake $(CMAKE_FLAGS) ..

doctest/doctest.h:
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
