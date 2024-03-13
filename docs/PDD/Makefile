rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
MD:=$(call rwildcard,md,*.md)
OUT:=ECE492_RISCV_PDD_V02.pdf
ENGINE:=xelatex
TEMPLATE:=custom.tex
FONTS:=$(patsubst %,ttf/Carlito-%.ttf,Regular Italic Bold BoldItalic)

UML_SRC:=$(call rwildcard,uml,*.uml)
UML_PNG:=$(UML_SRC:uml/%.uml=uml/%.png)

TIME:=time

TEX_SRC:=$(call rwildcard,tex,*.tex)
BIB:=biblio.bib
CSL:=ieee-with-url.csl
INPUTS:=$(MD) $(FONTS) $(TEMPLATE) $(TEX_SRC) $(CSL) $(BIB) $(UML_SRC)

XELATEX:=$(shell command -v xelatex 2> /dev/null)
PANDOC:=$(shell command -v pandoc 2> /dev/null)
PLANTUML:=$(shell command -v plantuml 2> /dev/null)

$(OUT): $(INPUTS) $(UML_PNG)
ifndef PANDOC
	$(error '`pandoc` not installed. Please run `sudo apt install pandoc`.')
endif
ifndef XELATEX
	$(error '`xelatex` not installed. Please run `sudo apt install texlive-xetex`.')
endif
	$(TIME) pandoc --bibliography=$(BIB) --template=$(TEMPLATE) --pdf-engine=$(ENGINE) $(MD) -o $@

watch: $(OUT)
	zathura $< &
	ls $(INPUTS) | entr sh -c 'make'

dev:
	ls $(INPUTS) | entr sh -c 'make'

uml/%.png: uml/%.uml
ifndef PLANTUML
	$(error '`plantuml` not installed. Please run `sudo apt install plantuml`.')
endif
	plantuml $<

$(CSL):
	wget -O $@ https://raw.githubusercontent.com/citation-style-language/styles/master/$(CSL)

# Font Stuff [[[

ttf/Carlito-Regular.ttf:
	wget -O $@ https://fonts.gstatic.com/s/carlito/v3/3Jn9SDPw3m-pk039PDCLTXUETuE.ttf
ttf/Carlito-Italic.ttf:
	wget -O $@ https://fonts.gstatic.com/s/carlito/v3/3Jn_SDPw3m-pk039DDKBSVcBXuFb0Q.ttf
ttf/Carlito-Bold.ttf:
	wget -O $@ https://fonts.gstatic.com/s/carlito/v3/3Jn4SDPw3m-pk039BIykaX0vUuhCyOo.ttf
ttf/Carlito-BoldItalic.ttf:
	wget -O $@ https://fonts.gstatic.com/s/carlito/v3/3Jn6SDPw3m-pk039DDK59XglVspH2OprMQ.ttf
# End Font Stuff ]]]

fmt:
	@for i in $(TEX_SRC); do latexindent -w -c=/tmp $$i >/dev/null; done

clean:
	rm -f $(OUT)

.PHONY: watch clean

# vim:foldmethod=marker foldmarker=[[[,]]]
