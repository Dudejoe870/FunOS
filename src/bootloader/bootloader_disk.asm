[bits 16]
disk_load:
    pusha

    push dx

    mov ah, 0x02
    mov al, dh
    mov cl, 0x02

    mov ch, 0x00
    mov dh, 0x00

    int 0x13
    jc .disk_error

    pop dx
    cmp al, dh
    jne .sector_error
    popa
    ret

    .disk_error:
        mov bx, DISK_ERROR
        call print
        call print_nl
        mov dh, ah
        call print_hex
        jmp .loop
    .sector_error:
        mov bx, SECTOR_ERROR
        call print
    .loop:
        jmp $

DISK_ERROR db "ERROR: FAILED TO READ DISK!", 0
SECTOR_ERROR db "ERROR: INCORRECT NUMBER OF SECTORS READ!", 0