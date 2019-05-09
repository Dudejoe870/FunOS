#include "syscall.h"

#include "tty.h"

void init_syscalls()
{
    register_syscall_handler(0, terminal_clear_syscall);
}

// Callbacks
// TTY:
void terminal_clear_syscall(interrupt_info_t* info)
{
    terminal_clear();
    terminal_setcurrentpos(0, 0);
}