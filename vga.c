#include "vga.h"

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
    return (uint16_t)uc | (uint16_t)color << 8;
}

size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void terminal_initialize(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t *)0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

bool is_terminal_filled()
{
    return terminal_column + 1 == VGA_WIDTH && terminal_row + 1 == VGA_HEIGHT;
}

void terminal_scroll()
{
    uint16_t *buffer = (uint16_t *)0xB8000;

    // replaces each character with the one right below it
    for (size_t temp_row = 0; temp_row < VGA_HEIGHT; temp_row++) // y
    {
        for (size_t temp_col = 0; temp_col < VGA_WIDTH; temp_col++) // x
        {
            const size_t current_index = temp_row * VGA_WIDTH + temp_col;
            const size_t replacement_index = ((temp_row + 1) * VGA_WIDTH) + temp_col;
            buffer[current_index] = buffer[replacement_index];
        }
    }

    // clean last line
    for (size_t temp_col = 0; temp_col < VGA_WIDTH; temp_col++)
    {
        const size_t current_index = (VGA_HEIGHT - 1) * VGA_WIDTH + temp_col;
        buffer[current_index] = vga_entry(' ', terminal_color);
    }

    terminal_column = 0;
    terminal_row = VGA_HEIGHT - 1;
}

void terminal_putchar(char c)
{
    if (is_terminal_filled())
    {
        terminal_scroll();
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    }
    else
    {
        if (c == '\n')
        {
            terminal_column = 0;
            terminal_row++;
        }
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH)
        {
            terminal_column = 0;
            terminal_row++;
        }
    }
}

void terminal_write(const char *data, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char *data)
{
    terminal_write(data, strlen(data));
}
