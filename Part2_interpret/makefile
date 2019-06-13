all: build

build: clean interpret.o
	ld -o interpret interpret.o

interpret.o: interpret.asm
	nasm -f elf64 -g -F dwarf interpret.asm -o interpret.o

clean:
	rm -f *.o
	rm -f interpret

run: build
	./interpret

test_third_part: build
	./interpret < third_part_script.interpret