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
cocasm.all: ocasm.c
	gcc -D OCASM_ALL=1 -Wall -Werror -o cocasm.all ocasm.c
