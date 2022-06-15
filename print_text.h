#pragma once
#include "IO.h"
#include "dtypes.h"
#include "colordefs.h"
#define VGA_MEMORY (uint_8*)0xB8000
#define VGA_WIDTH 80

extern uint_16 cursor_position;

void setCursorPosition(uint_16 position);
uint_16 getPositionFromCoordinates(uint_8 x, uint_8 y);
void print(const char* str, uint_8 color = BACKGROUND_BLACK | TEXT_LIGHTGREEN);
void printChar(char ch, uint_8 color = BACKGROUND_BLACK | TEXT_LIGHTGREEN);
void clear(uint_64 color = BACKGROUND_BLACK | TEXT_LIGHTGREEN);

const char* floatToString(float value, uint_8 decimals);
const char* hexToString(uint_8 value);
const char* hexToString(uint_16 value);
const char* hexToString(uint_32 value);
const char* hexToString(uint_64 value);
const char* hexToString(char value);
const char* hexToString(short value);
const char* hexToString(int value);
const char* hexToString(long long value);

const char* intToString(uint_8 value);
const char* intToString(uint_16 value);
const char* intToString(uint_32 value);
const char* intToString(uint_64 value);
const char* intToString(char value);
const char* intToString(short value);
const char* intToString(int value);
const char* intToString(long long value);
