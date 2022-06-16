#include "print_text.h"
#include "IDT.h"
#include "keyboard.h"
#include "memory_map.h"
#include "heap.h"

extern "C" void _start() {
	initIDT();
	setCursorPosition(0);
	kb_handler = keyboard_handler;
	MemoryMapEntry** usableRegions = getUsableRegions();
	initHeap(0x100000, 0x100000);
	
	

	return;
}