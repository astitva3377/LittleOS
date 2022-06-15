#include "print_text.h"

uint_16 cursor_position;

void setCursorPosition(uint_16 position) {
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint_8)(position & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint_8)((position >> 8) & 0xFF));
	cursor_position = position;
}

uint_16 getPositionFromCoordinates(uint_8 x, uint_8 y) {
	return y * VGA_WIDTH + x;
}

void print(const char* str, uint_8 color) {
	uint_8* ptr = (uint_8*)str;
	uint_16 idx = cursor_position;
	while (*ptr != 0) {
		switch(*ptr) {
			case 10: 
				idx += VGA_WIDTH - (idx%VGA_WIDTH);
				break;
			default:
				*(VGA_MEMORY + idx * 2) = *ptr;
				*(VGA_MEMORY + idx * 2 + 1) = color;
				idx++;
				break;
		}
		ptr++;
	}
	setCursorPosition(idx);
}

void printChar(char ch, uint_8 color) {
	*(VGA_MEMORY + cursor_position * 2) = ch;
	*(VGA_MEMORY + cursor_position * 2 + 1) = color;
	setCursorPosition(cursor_position + 1);
}

void clear(uint_64 color) {
	uint_64 val = 0;
	val += (color << 8 | color << 24 | color << 40 | color << 56);
	for(uint_64* i = (uint_64*)VGA_MEMORY; i < (uint_64*)(VGA_MEMORY + 4000); i++)
		*i = val;
}

char hexBuffer[128];
template<typename T>
const char* hexToString(T value) {
	T* ptr = &value;
	uint_8 size = (sizeof(T)) * 2 - 1;
	for(uint_8 i = 0; i < size; i++) {
		uint_8* p = ((uint_8*)ptr + i);
		uint_8 tmp = ((*p & 0xF0) >> 4);
		hexBuffer[size - (i * 2 + 1)] = tmp + (tmp > 9? 55: 48);
		tmp = ((*p & 0x0F));
		hexBuffer[size - (i * 2)] = tmp + (tmp > 9? 55: 48);
	}
	hexBuffer[size + 1] = 0;
	return hexBuffer;
}

const char* hexToString(uint_8 value) { return hexToString<uint_8>(value); }
const char* hexToString(uint_16 value) { return hexToString<uint_16>(value); }
const char* hexToString(uint_32 value) { return hexToString<uint_32>(value); }
const char* hexToString(uint_64 value) { return hexToString<uint_64>(value); }
const char* hexToString(char value) { return hexToString<char>(value); }
const char* hexToString(short value) { return hexToString<short>(value); }
const char* hexToString(int value) { return hexToString<int>(value); }
const char* hexToString(long long value) { return hexToString<long long>(value); }

char intBuffer[128];
template<typename T>
const char* intToString(T value) {
	uint_8 isNeg = 0;
	if(value < 0) {
		isNeg = 1;
		value *= -1;
		intBuffer[0] = '-';
	}
	uint_8 size = 0;
	uint_64 tsize = (uint_64)value;
	while(tsize/10 > 0) {
		tsize /= 10;
		size++;
	}
	uint_8 idx = 0;
	tsize = (uint_64)value;
	while(tsize / 10 > 0) {
		uint_8 rmdr = tsize % 10;
		tsize /= 10;
		intBuffer[isNeg + size - idx] = rmdr + 48;
		idx++;
	}
	uint_8 rmdr = tsize % 10;
	intBuffer[isNeg + size - idx] = rmdr + 48;
	intBuffer[isNeg + size + 1] = 0;
	return intBuffer;
}

const char* intToString(uint_8 value) { return intToString<uint_8>(value); }
const char* intToString(uint_16 value) { return intToString<uint_16>(value); }
const char* intToString(uint_32 value) { return intToString<uint_32>(value); }
const char* intToString(uint_64 value) { return intToString<uint_64>(value); }
const char* intToString(char value) { return intToString<char>(value); }
const char* intToString(short value) { return intToString<short>(value); }
const char* intToString(int value) { return intToString<int>(value); }
const char* intToString(long long value) { return intToString<long long>(value); }

char floatBuffer[128];
const char* floatToString(float value, uint_8 decimals) {
	char* intptr = (char*)intToString((int)value);
	char* floatptr = floatBuffer;
	if(value < 0)
		value *= -1;
	while(*intptr != 0) {
		*floatptr = *intptr;
		intptr++;
		floatptr++;
	}
	*floatptr = '.';
	floatptr++;
	float val = value - (int)value;
	for(uint_8 i = 0; i < decimals; i++) {
		val *= 10;
		*floatptr = (int)val + 48;
		val -= (int)val;
		floatptr++;
	}
	*floatptr = 0;
	return floatBuffer;
}