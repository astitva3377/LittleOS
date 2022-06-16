nasm bootstrap/bootloader.asm -f bin -o bootloader.bin
nasm kernel/arch/extended.asm -f elf64 -o extended.o
nasm kernel/memory/binary.asm -f elf64 -o binary.o
wsl %CGCC%/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -I headers -m64 -c kernel/kernel/kernel.cpp -o kernel.o
wsl %CGCC%/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -I headers -m64 -c kernel/arch/IDT.cpp -o IDT.o
wsl %CGCC%/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -I headers -m64 -c kernel/arch/IO.cpp -o IO.o
wsl %CGCC%/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -I headers -m64 -c kernel/kernel/keyboard.cpp -o keyboard.o
wsl %CGCC%/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -I headers -m64 -c kernel/memory/memory_map.cpp -o memory_map.o
wsl %CGCC%/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -I headers -m64 -c kernel/kernel/print_text.cpp -o print_text.o
wsl %CGCC%/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -I headers -m64 -c kernel/memory/heap.cpp -o heap.o
wsl %CGCC%/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -I headers -m64 -c kernel/memory/memory.cpp -o memory.o
wsl %CGCC%/x86_64-elf-ld -T link.ld
copy /b bootloader.bin+kernel.bin bootloader.flp
del *.bin *.o *.tmp