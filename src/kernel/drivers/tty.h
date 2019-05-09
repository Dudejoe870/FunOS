#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Macros
#define TERM_WIDTH 80 // The terminal width
#define TERM_HEIGHT 25 // The terminal height
#define TERM_SIZE TERM_WIDTH * TERM_HEIGHT // The entire size of the terminal

// General purpose variables
size_t terminal_row; // The current terminal row
size_t terminal_column; // The current terminal column
uint8_t terminal_color; // The current terminal color

volatile uint16_t* terminal_buffer; // The Video Pointer

void terminal_clear(void);
void terminal_initialize(void);
void terminal_update_cursor(void);
void terminal_setcurrentpos(size_t row, size_t column);
void terminal_setcolor(uint8_t color);
void terminal_putcharat(const char c, uint8_t color, size_t x, size_t y);
void terminal_scrolldown(bool shouldUpdateCursor);
void terminal_putchar(const char c, bool shouldUpdateCursor);
void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void terminal_disable_cursor();