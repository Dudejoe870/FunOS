#include "renderer.h"
#include "math.h"

void render_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, enum vga_color color)
{
    for (uint32_t sy = y; sy < height; sy++)
        for (uint32_t sx = x; sx < width; sx++)
            vga_put_pixel(sx, sy, color);
}

void render_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, enum vga_color color)
{
    int32_t x, y, xe, ye;

    int32_t dx = x2 - x1;
    int32_t dy = y2 - y1;

    int32_t dx1 = abs(dx);
    int32_t dy1 = abs(dy);

    int32_t px = 2 * dy1 - dx1;
    int32_t py = 2 * dx1 - dy1;

    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1;
            y = y1;
            xe = x2;
        }
        else
        {
            x = x2;
            y = y2;
            xe = x1;
        }

        vga_put_pixel(x, y, color);

        for (int i = 0; x < xe; i++)
        {
            x++;

            if (px < 0)
            {
                px = px + 2 * dy1;
            }
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    y++;
                }
                else
                {
                    y--;
                }
                px += 2 * (dy1 - dx1);
            }

            vga_put_pixel(x, y, color);
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        else
        {
            x = x2;
            y = y2;
            ye = y1;
        }

        vga_put_pixel(x, y, color);

        for (int i = 0; y < ye; i++)
        {
            y++;

            if (py <= 0)
            {
                py += 2 * dx1;
            }
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    x++;
                }
                else
                {
                    x--;
                }
                py += 2 * (dx1 - dy1);
            }

            vga_put_pixel(x, y, color);
        }
    }
}