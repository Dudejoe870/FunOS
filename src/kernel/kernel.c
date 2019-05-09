#include <stdbool.h>

#include "isr.h"
#include "tty.h"
#include "stdio.h"
#include "timer.h"
#include "keyboard.h"
#include "vga.h"
#include "renderer.h"
#include "shell.h"
#include "syscall.h"

extern void syscall_test(void);

void kernel_main()
{
    vga_set_mode(t_80x25);

    terminal_initialize();

    isr_install();
    init_syscalls();

    print_input = true;
    enable_shell = true;
    init_keyboard();

    while(true)
    {
        process_command();
    }
}