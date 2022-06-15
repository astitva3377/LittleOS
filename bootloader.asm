[org 0x7C00]

mov [boot_disk], dl

mov bp, 0x7C00
mov sp, bp

call read_disk

jmp program_space

%include "print.asm"
%include  "readdisk.asm"

times 510-($-$$) db 0
dw 0xAA55