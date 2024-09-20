all: bin/fyshls

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRC := $(call rwildcard,.,*.go)

install:
	go run cmd/install/main.go

release:
	go run cmd/release/main.go

test:
	go test ./...

bin/fyshls: $(SRC) | bin
	go run cmd/install/main.go $@

bin:
	mkdir $@
