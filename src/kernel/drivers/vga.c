#include "vga.h"

#include "io.h"

uint8_t vga_color(enum vga_color fg, enum vga_color bg) { return fg | bg << 4; }

uint16_t vga_char_entry(uint8_t c, uint8_t color) { return (uint16_t) c | (uint16_t) color << 8; }

void vga_write_registers(uint8_t* registers)
{
    outb(VGA_MISC_PORT, *(registers++));

    for (uint8_t i = 0; i < 5; i++)
    {
        outb(VGA_SEQ_INDEX_PORT, i);
        outb(VGA_SEQ_DATA_PORT, *(registers++));
    }

    outb(VGA_CRTC_INDEX_PORT, 0x03);
    outb(VGA_CRTC_DATA_PORT, inb(VGA_CRTC_DATA_PORT) | 0x80);
    outb(VGA_CRTC_INDEX_PORT, 0x11);
    outb(VGA_CRTC_DATA_PORT, inb(VGA_CRTC_DATA_PORT) & ~0x80);

    registers[0x03] = registers[0x03] | 0x80;
    registers[0x11] = registers[0x11] & ~0x80;

    for (uint8_t i = 0; i < 25; i++)
    {
        outb(VGA_CRTC_INDEX_PORT, i);
        outb(VGA_CRTC_DATA_PORT, *(registers++));
    }

    for (uint8_t i = 0; i < 9; i++)
    {
        outb(VGA_GFXC_INDEX_PORT, i);
        outb(VGA_GFXC_DATA_PORT, *(registers++));
    }

    for (uint8_t i = 0; i < 21; i++)
    {
        inb(VGA_ATTRC_RESET_PORT);
        outb(VGA_ATTRC_INDEX_PORT, i);
        outb(VGA_ATTRC_WRITE_PORT, *(registers++));
    }

    inb(VGA_ATTRC_RESET_PORT);
    outb(VGA_ATTRC_INDEX_PORT, 0x20);
}

bool vga_set_mode(enum video_mode mode)
{
    unsigned char g_320x200x256[] =
    {
    /* MISC */
        0x63,
    /* SEQ */
        0x03, 0x01, 0x0F, 0x00, 0x0E,
    /* CRTC */
        0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
        0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x9C, 0x0E, 0x8F, 0x28,	0x40, 0x96, 0xB9, 0xA3,
        0xFF,
    /* GC */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
        0xFF,
    /* AC */
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x41, 0x00, 0x0F, 0x00,	0x00
    };

    unsigned char g_80x25_text[] =
    {
    /* MISC */
        0x67,
    /* SEQ */
        0x03, 0x00, 0x03, 0x00, 0x02,
    /* CRTC */
        0x5F, 0x4F, 0x50, 0x82, 0x55, 0x81, 0xBF, 0x1F,
        0x00, 0x4F, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x50,
        0x9C, 0x0E, 0x8F, 0x28, 0x1F, 0x96, 0xB9, 0xA3,
        0xFF,
    /* GC */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
        0xFF,
    /* AC */
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
        0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
        0x0C, 0x00, 0x0F, 0x08, 0x00
    };
    
    switch (mode)
    {
        case v_320x200x256:
            vga_write_registers(g_320x200x256); 
            break;
        case t_80x25:
            vga_write_registers(g_80x25_text); 
            break;
    }
    
    return true;
}

uint8_t* vga_get_framebuffer_segment()
{
    outb(VGA_GFXC_INDEX_PORT, 0x06);
    uint8_t segmentNumber = inb(VGA_GFXC_DATA_PORT) & (3<<2);
    switch (segmentNumber)
    {
        default:
        case 0<<2: return (uint8_t*)0x00000;
        case 1<<2: return (uint8_t*)0xA0000;
        case 2<<2: return (uint8_t*)0xB0000;
        case 3<<2: return (uint8_t*)0xB8000;
    }
}

void vga_put_pixel(uint32_t x, uint32_t y, enum vga_color color)
{
    uint8_t* pixeladdr = vga_get_framebuffer_segment() + 320 * y + x;
    *pixeladdr = (uint8_t)color;
}