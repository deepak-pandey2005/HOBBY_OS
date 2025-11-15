#include "vga.h"
#include <stdint.h>

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
int terminal_row = 0;
int terminal_col = 0;

static inline uint16_t vga_entry(unsigned char c, uint8_t color) {
    return (uint16_t)c | (uint16_t)color << 8;
}

void vga_clear_screen() {
    uint16_t blank = vga_entry(' ', VGA_COLOR_BLACK);
    for (int y = 0; y < VGA_HEIGHT; y++)
        for (int x = 0; x < VGA_WIDTH; x++)
            vga_buffer[y * VGA_WIDTH + x] = blank;
    terminal_row = 0;
    terminal_col = 0;
}

void vga_put_char(char c, uint8_t color, int x, int y) {
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT)
        vga_buffer[y * VGA_WIDTH + x] = vga_entry(c, color);
}

void vga_print(const char* str, uint8_t color) {
    while (*str) {
        if (*str == '\n') {
            terminal_col = 0;
            terminal_row++;
        } else {
            vga_put_char(*str, color, terminal_col, terminal_row);
            terminal_col++;
            if (terminal_col >= VGA_WIDTH) {
                terminal_col = 0;
                terminal_row++;
            }
        }
        if (terminal_row >= VGA_HEIGHT)
            terminal_row = 0;  // simple wrap
        str++;
    }
}
