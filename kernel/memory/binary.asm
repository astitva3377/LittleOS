%macro inc_bin 2
	SECTION .rodata
	GLOBAL %1
%1:
	incbin %2
	db 0
	%1_size: dq %1_size - %1
%endmacro

inc_bin test, "test.txt"