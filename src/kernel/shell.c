#include "shell.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "tty.h"
#include "vga.h"

#define UNKNOWN_CMD_MSG "Unknown Command.\n"

bool commandIsQueued;
char currCommand[256];

char** get_args(char* input, uint32_t* len)
{
    char** res = malloc(sizeof(char*) * 256);

    char* tok;
    int i = 0;

    while (true)
    {
        tok = strtok(input, " ");
        if (tok == NULL) break;
        res[i++] = tok;
    }
    *len = i;

    return res;
}

// Because this is called inside an interrupt, it's better to process the command after the interrupt is over, just in case.
void user_input(char* input)
{
    uint32_t inputLen = strlen(input);
    uint32_t i;
    for (i = 0; i < inputLen; i++)
    {
        currCommand[i] = input[i];
    }
    currCommand[i+1] = 0;
    commandIsQueued = true;
}

void process_command()
{
    if (commandIsQueued)
    {
        uint32_t args_len = 0;
        char** args = get_args(currCommand, &args_len);
        if (strcmp(args[0], "clear") == 0)
        {
            terminal_clear();
            terminal_row = 0;
            terminal_column = 0;
            terminal_update_cursor();
        }
        else
        {
            terminal_setcolor(vga_color(VGA_COLOR_RED, VGA_COLOR_BLACK));
            puts(UNKNOWN_CMD_MSG);
            terminal_setcolor(vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
        }
        commandIsQueued = false;
        uint32_t commandLen = strlen(currCommand);
        for (uint32_t i = 0; i < commandLen; i++)
            currCommand[i] = 0;
    }
}
