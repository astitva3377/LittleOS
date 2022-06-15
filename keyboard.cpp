#pragma once
#include "IDT.cpp"
#include "dtypes.cpp"

bool lshiftheld = false, rshiftheld = false;
uint_8 prev_code;

void std_keyboard_handler(uint_8 code, uint_8 ch) {
	if(ch != 0) {
		switch(lshiftheld || rshiftheld) {
			case true:
				printChar(ch - 32);
				break;
			case false:
				printChar(ch);
				break;
		}
	} else {
		switch(code) {
			case 0x8E: //backspace
				setCursorPosition(cursor_position - 1);
				printChar(' ');
				setCursorPosition(cursor_position - 1);
				break;
			case 0x2A: //Lshift
				lshiftheld = true;
				break;
			case 0xAA: //Lshift release
				lshiftheld = false;
				break;
			case 0x36: //Rshift
				rshiftheld = true;
				break;
			case 0xB6: //Rshift release
				rshiftheld = false;
				break;
			case 0x9C: //enter
				print("\n");
				break;
		}
	}
}

void handleE0(uint_8 code) {
	switch(code) {
		case 0x50:
			setCursorPosition(cursor_position + VGA_WIDTH);
			break;
		case 0x48:
			setCursorPosition(cursor_position - VGA_WIDTH);
			break; 
	}
}

void keyboard_handler(uint_8 code, uint_8 ch) {
	switch(prev_code) {
		case 0xE0:
			handleE0(code);
			break;
		default:
			std_keyboard_handler(code, ch);
	}
	prev_code = code;
}