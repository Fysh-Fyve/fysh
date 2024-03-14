NINJA := $(shell command -v ninja 2> /dev/null)

ifdef NINJA
BUILD ?= ninja
CMAKE_FLAGS += -GNinja
else
BUILD ?= $(MAKE) -s
endif

ifdef RELEASE
CMAKE_FLAGS += -DCMAKE_BUILD_TYPE=Release
endif

.PHONY: all
all: doctest/doctest.h build/compile_commands.json | build
	cd build && $(BUILD)

.PHONY: test
test: all
	./build/test/tests

.PHONY: release
release:
	rm -rf build
	RELEASE=1 $(MAKE) all

.PHONY: install
install:
	cp ./build/fysh-sea /usr/local/bin/fysh-sea

.PHONY: clean
clean: build
	cd build && $(BUILD) clean

build/compile_commands.json: build
	cd build && cmake $(CMAKE_FLAGS) ..

doctest/doctest.h:
	wget -O $@ https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h

build:
	mkdir -p $@

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRC := $(call rwildcard,src,*.cc) \
       $(call rwildcard,src,*.h) \
       $(call rwildcard,test,*.cc) \
       $(call rwildcard,test,*.h) \
       $(call rwildcard,asm,*.cc) \
       $(call rwildcard,asm,*.h)

DPRINT := $(shell command -v dprint 2> /dev/null)

.PHONY: fmt
fmt: $(SRC)
	clang-format -i $^
ifdef DPRINT
	dprint fmt
endif
