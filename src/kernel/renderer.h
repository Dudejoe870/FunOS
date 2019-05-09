#pragma once

#include "vga.h"

void render_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, enum vga_color color);
void render_line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, enum vga_color color);