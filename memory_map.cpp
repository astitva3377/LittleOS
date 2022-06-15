#include "memory_map.h"

uint_8 usableRegionCount;
MemoryMapEntry* usableRegions[10];

void printMemoryMap(MemoryMapEntry* map, uint_16 position) {
	setCursorPosition(position);
	print("Memory Base: "); print(intToString(map->baseAddr));
	setCursorPosition(position + 80);
	print("Region Length: "); print(intToString(map->regionLength));
	setCursorPosition(position + 160);
	print("Memory Type: "); print(intToString(map->regionType));
	setCursorPosition(position + 240);
	print("Memory Attributes: "); print(hexToString(map->extendedAttr));
	setCursorPosition(position + 400);
}

bool regionsAcquired = false;

MemoryMapEntry** getUsableRegions() {
	if(regionsAcquired) {
		return usableRegions;
	}
	uint_8 regionIdx;
	for(uint_8 i = 0; i < memory_region_count; i++) {
		MemoryMapEntry* map = (MemoryMapEntry*)0x5000;
		map += i;
		if(map->regionType == 1) {
			usableRegions[regionIdx] = map;
			regionIdx++;
		}
	}
	usableRegionCount = regionIdx;
	regionsAcquired = true;
	return usableRegions;
}