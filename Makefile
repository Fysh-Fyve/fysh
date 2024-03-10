all: bin/fyshls

test:
	go test ./...

bin/fyshls: main.go | bin
	go build -o $@

bin:
	mkdir $@
