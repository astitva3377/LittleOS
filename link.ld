OUTPUT_FORMAT(binary)
ENTRY(_start)
INPUT
(
	extended.o
	kernel.o
	IDT.o
	IO.o
	memory_map.o
	print_text.o
	keyboard.o
	heap.o
	memory.o
	binary.o
)

OUTPUT
(
	kernel.bin
)

SECTIONS
{
	. = 0x8000;
	.text : ALIGN(0x1000)
	{
		*(.text)
	}

	.idt BLOCK(0x1000) : ALIGN(0x1000)
	{
		_idt = .;
		. = . + 0x1000;
	}

	.data : ALIGN(0x1000)
	{
		*(.data)
	}

	.rodata : ALIGN(0x1000)
	{
		*(.rodata)
	}

	.bss : ALIGN(0x1000)
	{
		*(COMMON)
		*(.bss)
	}
}