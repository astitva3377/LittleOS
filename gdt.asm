gdt_null_desc:
	dd 0
	dd 0

gdt_code_desc:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10011010b
	db 11001111b
	db 0x00

gdt_data_desc:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10010010b
	db 11001111b
	db 0x00

gdt_end:

gdt_desc:
	get_size:
		dw gdt_end - gdt_null_desc - 1
		dq gdt_null_desc

codeseg equ gdt_code_desc - gdt_null_desc
dataseg equ gdt_data_desc - gdt_null_desc

[bits 32]

edit_gdt:
	mov [gdt_code_desc + 6], byte 10101111b
	mov [gdt_data_desc + 6], byte 10101111b
	ret

[bits 16]