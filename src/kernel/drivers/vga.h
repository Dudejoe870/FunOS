#pragma once

#include <stdint.h>
#include <stdbool.h>

enum vga_color
{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_LIGHT_GRAY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_DARK_GRAY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15
};

enum video_mode
{
	t_80x25,
	v_320x200x256
};

#define VGA_MISC_PORT 0x3C2
#define VGA_CRTC_INDEX_PORT 0x3D4
#define VGA_CRTC_DATA_PORT 0x3D5
#define VGA_SEQ_INDEX_PORT 0x3C4
#define VGA_SEQ_DATA_PORT 0x3C5
#define VGA_GFXC_INDEX_PORT 0x3CE
#define VGA_GFXC_DATA_PORT 0x3CF
#define VGA_ATTRC_INDEX_PORT 0x3C0
#define VGA_ATTRC_READ_PORT 0x3C1
#define VGA_ATTRC_WRITE_PORT 0x3C0
#define VGA_ATTRC_RESET_PORT 0x3DA

uint8_t vga_color(enum vga_color fg, enum vga_color bg);

uint16_t vga_char_entry(uint8_t c, uint8_t color);

bool vga_set_mode(enum video_mode mode);

void vga_put_pixel(uint32_t x, uint32_t y, enum vga_color color);