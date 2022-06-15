program_space equ 0x8000

read_disk:
	mov ah, 0x02
	mov bx, program_space
	mov al, 32
	mov dl, [boot_disk]
	mov ch, 0x00
	mov dh, 0x00
	mov cl, 0x02
	int 0x13
	je disk_read_failed
	ret

boot_disk:
	db 0

disk_read_error_string:
	db 'Disk read failed', 0

disk_read_failed:
	mov bx, disk_read_error_string
	call print_string
	jmp $