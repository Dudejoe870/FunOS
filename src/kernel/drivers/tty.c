#include "tty.h"
#include "vga.h"
#include "io.h"
#include "string.h"

void terminal_clear(void) { for (size_t i = 0; i < TERM_SIZE; ++i) terminal_buffer[i] = vga_char_entry(' ', terminal_color); } // Clears the entire screen

// Initalizes the terminal for use
void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*)0xB8000;
	terminal_clear();
	terminal_update_cursor();
}

void terminal_update_cursor(void)
{
	uint16_t pos = terminal_row * TERM_WIDTH + terminal_column;
	
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void terminal_setcurrentpos(size_t row, size_t column) { terminal_row = row; terminal_column = column; terminal_update_cursor(); } // Sets the current position and updates the cursor
void terminal_setcolor(uint8_t color) { terminal_color = color; } // Sets the current color
void terminal_putcharat(const char c, uint8_t color, size_t x, size_t y) { if (c != '\n' || c != '\r') { terminal_buffer[y * TERM_WIDTH + x] = vga_char_entry(c, color); } } // Puts a char at a specified position

void terminal_scrolldown(bool shouldUpdateCursor)
{
	for (size_t y = 1; y < TERM_HEIGHT; ++y)
		memmove((void*)&terminal_buffer[((y - 1) * TERM_WIDTH)], (void*)&terminal_buffer[y * TERM_WIDTH], TERM_WIDTH * sizeof(uint16_t));

	for (size_t i = (TERM_HEIGHT - 1) * TERM_WIDTH; i < TERM_SIZE; ++i) terminal_buffer[i] = vga_char_entry(' ', terminal_color);
	terminal_column = 0;

	if (shouldUpdateCursor)
		terminal_update_cursor();
}

// Puts a char and updates the cursor
void terminal_putchar(const char c, bool shouldUpdateCursor) 
{
	if (c == '\n') 
	{
		if (++terminal_row >= TERM_HEIGHT)
		{
			--terminal_row;
			terminal_scrolldown(false);
		}
		terminal_column = 0;
	}
	else if (c == '\r') 
	{
		terminal_column = 0;
	}
	else 
	{
		terminal_putcharat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column > TERM_WIDTH) 
		{
			terminal_column = 0;
			if (++terminal_row >= TERM_HEIGHT)
			{
				--terminal_row;
				terminal_scrolldown(false);
			}
		}
	}

	if (shouldUpdateCursor)
		terminal_update_cursor();	
}

// Text Mode Cursor Functions
void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end) 
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
	
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3E0) & 0xE0) | cursor_end);
}

void terminal_disable_cursor() { outb(0x3D4, 0x0A); outb(0x3D5, 0x20); }