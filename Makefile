.PHONY: all
all: pytest ctest
	
pytest: ocasm rom.asm
	python ocasm rom.asm > pytest

ctest: cocasm rom.asm
	./cocasm rom.asm > ctest

cocasm: ocasm.c
	gcc -Wall -Werror -o cocasm ocasm.c
