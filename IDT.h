#pragma once
#include "dtypes.h"
#include "kb_int_code.h"
#include "IO.h"
#include "print_text.h"

struct IDT64 {
	uint_16 offset_low;
	uint_16 selector;
	uint_8 ist;
	uint_8 types_attr;
	uint_16 offset_mid;
	uint_32 offset_high;
	uint_32 zero;
};

extern void (*kb_handler)(uint_8 code, uint_8 ch);
void initIDT();