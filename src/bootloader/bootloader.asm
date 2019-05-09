[org 0x7c00]

KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl
mov bp, 0x9000
mov sp, bp

call load_kernel
call load_pm
jmp $

%include 'src/bootloader/bootloader_print.asm'
%include 'src/bootloader/bootloader_disk.asm'
%include 'src/bootloader/bootloader_gdt.asm'
%include 'src/bootloader/bootloader_print32.asm'
%include 'src/bootloader/bootloader_loadpm.asm'

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET
    mov dh, 45
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE db 0

times 510-($-$$) db 0
dw 0xAA55