jmp enter_protected_mode

%include "gdt.asm"
%include "print.asm"
%include "memory_info.asm"

enter_protected_mode:
	call detect_used_memory
	call enable_a20
	cli
	lgdt [gdt_desc]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp codeseg:start_protected_mode

enable_a20:
	in al, 0x92
	or al, 2
	out 0x92, al
	ret

[bits 32]

%include "cpuid.asm"
%include "pager.asm"

start_protected_mode:
	mov ax, dataseg
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call fetch_cpu_id
	call has_long_mode
	call set_up_identity_paging
	call edit_gdt
	jmp codeseg:start_64_bit

[bits 64]
[extern _start]

%include "IDT.asm"

start_64_bit:
	mov edi, 0xB8000
	mov rax, 0x0A200A200A200A20
	mov ecx, 500
	rep stosq
	call activate_sse
	call _start
	jmp $

activate_sse:
	mov rax, cr0
	and ax, 0b11111101
	or ax, 0b00000001
	mov cr0, rax

	mov rax, cr4
	or ax, 0b1100000000
	mov cr4, rax
	ret

times 2048-($-$$) db 0