#pragma once

#include <stdbool.h>
#include <stdint.h>

bool print_input;
bool enable_shell;

void init_keyboard(void);
bool is_key_down(uint8_t scancode);