#include "heap.h"

MemorySegmentHeader* firstFreeSegment;

void initHeap(uint_64 addr, uint_64 length) {
	firstFreeSegment = (MemorySegmentHeader*)addr;
	firstFreeSegment->memoryLength = length - (sizeof(MemorySegmentHeader));
	firstFreeSegment->next = 0;
	firstFreeSegment->prev = 0;
	firstFreeSegment->nextFree = 0;
	firstFreeSegment->prevFree = 0;
	firstFreeSegment->free = true;
}

void* malloc(uint_64 size) {
	uint_64 rmdr = size % 8;
	size -= rmdr;
	if(rmdr != 0) size += 8;
	MemorySegmentHeader* cSegment = firstFreeSegment;
	while(true) {
		if(cSegment->memoryLength >= size) {
			if(cSegment->memoryLength > size + sizeof(MemorySegmentHeader)) {
				MemorySegmentHeader* nSegment = (MemorySegmentHeader*)((uint_64)cSegment + sizeof(MemorySegmentHeader) + size);
				nSegment->free = true;
				nSegment->memoryLength = ((uint_64)cSegment->memoryLength - sizeof(MemorySegmentHeader) - size);
				nSegment->nextFree = cSegment->nextFree;
				nSegment->next = cSegment->next;
				nSegment->prev = cSegment;
				nSegment->prevFree = cSegment->prevFree;
				cSegment->nextFree = nSegment;
				cSegment->next = nSegment;
				cSegment->memoryLength = size;
			}
			if(cSegment == firstFreeSegment) {
				firstFreeSegment = cSegment->nextFree;
			}
			cSegment->free = false;
			if(cSegment->prevFree != 0) cSegment->prevFree->nextFree = cSegment->nextFree;
			if(cSegment->nextFree != 0) cSegment->nextFree->prevFree = cSegment->prevFree;
			if(cSegment->prev != 0) cSegment->prev->nextFree = cSegment->nextFree;
			if(cSegment->next != 0) cSegment->next->prevFree = cSegment->prevFree;
			return cSegment + 1;
		}
		if(cSegment->nextFree == 0) {
			return 0;
		}
		cSegment = cSegment->nextFree;
	}
	return 0;
}

void mergeFreeSegments(MemorySegmentHeader* a, MemorySegmentHeader* b) {
	if(a == 0 || b == 0) return;
	if(a < b) {
		a->memoryLength += b->memoryLength + sizeof(MemorySegmentHeader);
		a->next = b->next;
		a->nextFree = b->nextFree;
		b->next->prev = a;
		b->next->prevFree = a;
		b->nextFree->prevFree = a;
	} else {
		b->memoryLength += a->memoryLength + sizeof(MemorySegmentHeader);
		b->next = a->next;
		b->nextFree = a->nextFree;
		a->next->prev = b;
		a->next->prevFree = b;
		a->nextFree->prevFree = b;
	}
}

void free(void* addr) {
	MemorySegmentHeader* cSegment;
	AlignedMemorySegmentHeader* header = (AlignedMemorySegmentHeader*)addr - 1;
	if(header->isAligned) {
		cSegment = (MemorySegmentHeader*)(uint_64)header->headerAddr;
	} else {
		cSegment = ((MemorySegmentHeader*)addr) - 1;
	}
	cSegment->free = true;
	if(cSegment < firstFreeSegment) firstFreeSegment = cSegment;
	if(cSegment->nextFree != 0) {
		if(cSegment->nextFree->prevFree < cSegment)
			cSegment->nextFree->prevFree = cSegment;
	}
	if(cSegment->prevFree != 0) {
		if(cSegment->prevFree->nextFree > cSegment)
			cSegment->prevFree->nextFree = cSegment;
	}
	if(cSegment->next != 0) {
		cSegment->next->prev = cSegment;
		if(cSegment->next->free)
			mergeFreeSegments(cSegment, cSegment->next);
	}
	if(cSegment->prev != 0){
		cSegment->prev->next = cSegment;
		if(cSegment->prev->free)
			mergeFreeSegments(cSegment, cSegment->prev);
	}
}

void* calloc(uint_64 size) {
	void* addr = malloc(size);
	memset(addr, 0, size);
	return addr;
}

void* calloc(uint_64 val, uint_64 size) {
	return calloc(val * size);
}

void* realloc(void* addr, uint_64 size) {
	MemorySegmentHeader* old;
	AlignedMemorySegmentHeader* header = (AlignedMemorySegmentHeader*)addr - 1;
	if(header->isAligned) {
		old = (MemorySegmentHeader*)(uint_64)header->headerAddr;
	} else {
		old = ((MemorySegmentHeader*)addr) - 1;
	}
	uint_64 smaller = size;
	if(old->memoryLength < size) smaller = old->memoryLength;
	void* naddr = malloc(size);
	memcpy(naddr, addr, smaller);
	free(addr);
	return naddr;
}

void* aligned_alloc(uint_64 alignment, uint_64 size) {
	uint_64 alignrmdr = alignment % 8;
	alignment -= alignrmdr;
	if(alignrmdr != 0) alignment += 8;
	uint_64 sizermdr = size % 8;
	size -= sizermdr;
	if(sizermdr != 0) size += 8;
	uint_64 full = size + alignment;
	void* maddr = malloc(full);
	uint_64 addr = (uint_64)maddr;
	uint_64 rmdr = addr % alignment;
	addr -= rmdr;
	if(rmdr != 0) {
		addr += alignment;
		AlignedMemorySegmentHeader* header = (AlignedMemorySegmentHeader*)addr - 1;
		header->isAligned = true;
		header->headerAddr = (uint_64)maddr - sizeof(MemorySegmentHeader);
	}
	return (void*)addr;
}