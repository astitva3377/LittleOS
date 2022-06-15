#pragma once
#include "dtypes.cpp"
#include "IO.cpp"
#include "print_text.cpp"
#include "kb_int_code.cpp"

struct IDT64 {
	uint_16 offset_low;
	uint_16 selector;
	uint_8 ist;
	uint_8 types_attr;
	uint_16 offset_mid;
	uint_32 offset_high;
	uint_32 zero;
};

extern IDT64 _idt[256];
extern uint_64 isr1;
extern "C" void load_idt();

void initIDT() {
	_idt[1].zero = 0;
	_idt[1].offset_low = (uint_16)(((uint_64)&isr1 & 0x000000000000FFFF));
	_idt[1].offset_mid = (uint_16)(((uint_64)&isr1 & 0x00000000FFFF0000) >> 16);
	_idt[1].offset_mid = (uint_16)(((uint_64)&isr1 & 0xFFFFFFFF00000000) >> 32);
	_idt[1].ist = 0;
	_idt[1].selector = 0x08;
	_idt[1].types_attr = 0x8E;
	remapPIC();
	outb(0x21, 0xFD);
	outb(0xA1, 0xFF);
	load_idt();
}

void (*kb_handler)(uint_8 code, uint_8 ch);

extern "C" void isr1_handler() {
	uint_8 code = inb(0x60);
	uint_8 ch = 0;
	if(code < 0x3A)
		ch = keycode[code];
	if(kb_handler != 0)
		kb_handler(code, ch);
	outb(0x20, 0x20);
	outb(0xA0, 0x20);
}