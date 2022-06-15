#include "print_text.cpp"
#include "IDT.cpp"
#include "keyboard.cpp"

extern "C" void _start() {
	initIDT();
	setCursorPosition(0);
	kb_handler = keyboard_handler;
	print(intToString(123456789));
	print("\n");
	print(intToString(-500));
	return;
}