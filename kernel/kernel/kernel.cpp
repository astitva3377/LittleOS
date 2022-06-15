#include "print_text.h"
#include "IDT.h"
#include "keyboard.h"
#include "memory_map.h"

extern "C" void _start() {
	initIDT();
	setCursorPosition(0);
	kb_handler = keyboard_handler;
	MemoryMapEntry** usableRegions = getUsableRegions();
	for(uint_8 i = 0; i < usableRegionCount; i++) {
		MemoryMapEntry* map = usableRegions[i];
		printMemoryMap(map, cursor_position);
	}
	return;
}