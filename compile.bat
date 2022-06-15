nasm bootloader.asm -f bin -o bootloader.bin
nasm extended.asm -f elf64 -o extended.o
nasm binary.asm -f elf64 -o binary.o
wsl %CGCC%/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c kernel.cpp -o kernel.o
wsl %CGCC%/x86_64-elf-ld -T link.ld
copy /b bootloader.bin+kernel.bin bootloader.flp
del *.bin *.o *.tmp