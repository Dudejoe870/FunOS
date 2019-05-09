#pragma once

#include "isr.h"

void init_syscalls(void);

// Callbacks
// TTY:
void terminal_clear_syscall(interrupt_info_t* info);