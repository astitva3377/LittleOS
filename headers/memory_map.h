#pragma once
#include "dtypes.h"
#include "print_text.h"

struct MemoryMapEntry {
	uint_64 baseAddr;
	uint_64 regionLength;
	uint_32 regionType;
	uint_32 extendedAttr;
};

extern uint_8 memory_region_count;
extern uint_8 usableRegionCount;

void printMemoryMap(MemoryMapEntry* map, uint_16 position);
MemoryMapEntry** getUsableRegions();