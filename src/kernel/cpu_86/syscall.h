#pragma once

#include "isr.h"

void init_syscalls(void);

// Callbacks
// TTY:
uint32_t terminal_clear_syscall(interrupt_info_t* info);