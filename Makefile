.PHONY: all
all: pytest ctest gotest

.PHONY: clean
clean:
	rm -f pytest ctest gotest out.oca
	rm -f cocasm
	
pytest: ocasm rom.asm
	time python ocasm rom.asm
	cp out.oca pytest

ocasm:
	ls -l ocasm

ctest: cocasm rom.asm
	time ./cocasm rom.asm
	cp out.oca ctest

cocasm: ocasm.c
	gcc -Wall -Werror -g -o cocasm ocasm.c

gotest: gocasm rom.asm
	time ./gocasm rom.asm
	cp out.oca gotest

gocasm: ocasm.go
	go build -o gocasm ocasm.go
