[bits 32]

global syscall_test

syscall_test:
    mov eax, 0
    int 0x80
    ret