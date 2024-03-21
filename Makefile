all: bin/fyshls

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRC := $(call rwildcard,.,*.go)

install:
	./build.sh

test:
	go test ./...

bin/fyshls: $(SRC) | bin
	./build.sh $@

bin:
	mkdir $@
