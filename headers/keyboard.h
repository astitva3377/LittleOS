#pragma once
#include "IDT.h"
#include "dtypes.h"

extern bool lshiftheld, rshiftheld;
extern uint_8 prev_code;

void std_keyboard_handler(uint_8 code, uint_8 ch);
void handleE0(uint_8 code);
void keyboard_handler(uint_8 code, uint_8 ch);