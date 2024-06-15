all: bin/fyshls

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRC := $(call rwildcard,.,*.go)

install:
	go run cmd/install/main.go

test:
	go test ./...

bin/fyshls: $(SRC) | bin
	go run cmd/install/main.go $@

bin:
	mkdir $@



release: export VERSION := $(shell git describe --tags --always --abbrev=0 --match='v[0-9]*.[0-9]*.[0-9]*' 2> /dev/null | sed 's/^.//')
release: export PACKAGE := "github.com/Fysh-Fyve/fyshls"
release: export COMMIT_HASH := $(shell git rev-parse --short HEAD)
release: export BUILD_TIMESTAMP=$(shell date '+%Y-%m-%dT%H:%M:%S')
release:
	go build -o fyshls -ldflags="-X '$(PACKAGE)/version.version=$(VERSION)' -X '$(PACKAGE)/version.commitHash=$(COMMIT_HASH)' -X '$(PACKAGE)/version.buildTimestamp=$(BUILD_TIMESTAMP)' -X '$(PACKAGE)/version.LogStderr=true'"
