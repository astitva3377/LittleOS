#pragma once
#include "dtypes.h"
#include "memory.h"

struct MemorySegmentHeader {
	uint_64 memoryLength;
	MemorySegmentHeader* prev;
	MemorySegmentHeader* next;
	MemorySegmentHeader* nextFree;
	MemorySegmentHeader* prevFree;
	bool free;
};

struct AlignedMemorySegmentHeader {
	uint_64 headerAddr : 63;
	bool isAligned : 1;
};

void initHeap(uint_64 addr, uint_64 length);
void* malloc(uint_64 size);
void* calloc(uint_64 size);
void* calloc(uint_64 val, uint_64 size);
void* realloc(void* addr, uint_64 size);
void free(void* addr);
void* aligned_alloc(uint_64 alignment, uint_64 size);