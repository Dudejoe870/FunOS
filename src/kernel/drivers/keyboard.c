#include "keyboard.h"
#include "io.h"
#include "isr.h"
#include "stdio.h"
#include "tty.h"
#include "shell.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

#define LINE_WIDTH 79

bool shift = false;
char key_buffer[LINE_WIDTH];
int key_buffer_index = 0;

#define SC_MAX 57
const char sc_ascii_noshift[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y', 
    'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g', 
    'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
    'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};

const char sc_ascii_shift[] = { '?', '?', '!', '@', '#', '$', '%', '^',     
    '&', '*', '(', ')', '_', '+', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
    'U', 'I', 'O', 'P', '{', '}', '?', '?', 'A', 'S', 'D', 'F', 'G', 
    'H', 'J', 'K', 'L', ':', '"', '~', '?', '|', 'Z', 'X', 'C', 'V', 
    'B', 'N', 'M', '<', '>', '?', '?', '?', '?', ' '};

static void keyboard_callback(interrupt_info_t* info)
{
    uint8_t scancode = inb(0x60);

    if (scancode == 0x2A)
    {
        shift = true;
        return;
    }
    else if (scancode == 0x2A + 0x80)
    {
        shift = false;
        return;
    }

    if (scancode > SC_MAX) return;
    if (scancode == ENTER)
    {
        if (print_input) putchar('\n');
        if (enable_shell) user_input(key_buffer);
        for (int i = 0; i < LINE_WIDTH; i++)
            key_buffer[i] = '\0';
        key_buffer_index = 0;
    }
    else if (scancode == BACKSPACE)
    {
        if (terminal_column <= 0 && print_input) return;
        key_buffer[key_buffer_index] = '\0';
        if (key_buffer_index > 0) key_buffer_index--;
        if (print_input)
        {
            terminal_column--;
            putchar(' ');
            terminal_column--;
            terminal_update_cursor();
        }
    }
    else
    {
        char ascii = ' ';
        if (shift)
            ascii = sc_ascii_shift[scancode];
        else
            ascii = sc_ascii_noshift[scancode];
        key_buffer[key_buffer_index++] = ascii;
        if (key_buffer_index > LINE_WIDTH) 
        {
            key_buffer_index = LINE_WIDTH;
            return;
        }
        if (print_input) putchar(ascii);
    }
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}