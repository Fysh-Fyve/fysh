rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

GO_MAINS:=$(call rwildcard,cmd,*/main.go)
GO_BINS:=$(GO_MAINS:cmd/%/main.go=cmd/out/%)

docs:
	git submodule init
	git submodule update
	doxygen

bins: $(GO_BINS)

serve: docs
	serve html

pages: cmd/out/deploy
	rm -rf html
	$(MAKE) docs
	cd docs/PDD && $(MAKE)
	@cp docs/*.pdf docs/**/*.pdf html/
	./$<

cmd/out/%: cmd/%/main.go
	go build -o $@ $<

.PHONY: docs serve pages bins
