#include "vga.h"
#include "keyboard.h"

void kmain() {
    vga_clear_screen();
    vga_print("Deepak OS Booted!\n", 0x0F);

    kbd_init();

    while (1) {
        char c = kbd_get_char();
        if (!c) continue;

        if (c == '\b') {  // backspace
            if (terminal_col > 0) terminal_col--;
            vga_put_char(' ', 0x0F, terminal_col, terminal_row);
        } else {
            vga_put_char(c, 0x0F, terminal_col, terminal_row);
            terminal_col++;
            if (terminal_col >= VGA_WIDTH) {
                terminal_col = 0;
                terminal_row++;
                if (terminal_row >= VGA_HEIGHT)
                    terminal_row = 0; // wrap for now
            }
        }
    }
}
