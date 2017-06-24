compile_c=gcc
compile_asm=nasm

b2x:
	$(compile_c) b2x.c -o b2x

#compila o arquivo executavel do windows
windows:
	$(compile_asm) -f win32 -o pe.o pe.asm
	$(compile_c) pe.o -o pe.dat
	del pe.o
	
#compila o arquivo executavel do linux
linux:
	$(compile_asm) -f elf32 -o elf.o elf.asm
	$(compile_c) elf.o -o elf.dat
	rm elf.o

#necessario ter o gcc instalado no wine
wine-windows:
	$(compile_asm) -f win32 -o pe.o pe.asm
	wine $(compile_c) pe.o -o pe.dat
	rm pe.o
