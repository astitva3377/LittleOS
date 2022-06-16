#include "memory.h"

void memset(void* start, uint_64 val, uint_64 size) {
	if(size <= 8) {
		uint_8* ptr = (uint_8*)&val;
		for(uint_8* i = (uint_8*)start; i < (uint_8*)((uint_64)start + size); i++) {
			*i = *ptr;
			ptr++;
		}
		return;
	}
	uint_64 pbytes = size % 8;
	uint_64 t = size - pbytes;
	for(uint_64* i = (uint_64*)start; i < (uint_64*)((uint_64)start + size); i++)
		*i = val;
	uint_8* ptr = (uint_8*)&val;
	for(uint_8* i = (uint_8*)((uint_64)start + t); i < (uint_8*)((uint_64)start + size); i++) {
		*i = *ptr;
		ptr++;
	}
}

void memcpy(void* dest, void* src, uint_64 size) {
	if(size <= 8) {
		uint_8* ptr = (uint_8*)src;
		for(uint_8* i = (uint_8*)dest; i < (uint_8*)((uint_64)dest + size); i++) {
			*i = *ptr;
			ptr++;
		}
		return;
	}
	uint_64 pbytes = size % 8;
	uint_64 t = size - pbytes;
	uint_64* srcptr = (uint_64*)src;
	for(uint_64* i = (uint_64*)dest; i < (uint_64*)((uint_64)dest + size); i++, srcptr++)
		*i = *srcptr;
	uint_8* ptr = (uint_8*)((uint_64)src + t);
	for(uint_8* i = (uint_8*)((uint_64)dest + t); i < (uint_8*)((uint_64)dest + size); i++) {
		*i = *ptr;
		ptr++;
	}
}