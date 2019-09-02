.PHONY: all
all: pytest ctest
	
pytest: ocasm rom.asm
	python ocasm rom.asm > pytest

ocasm:
	ls -l ocasm

ctest: cocasm rom.asm
	./cocasm rom.asm > ctest

cocasm: ocasm.c
	gcc -Wall -Werror -o cocasm ocasm.c
