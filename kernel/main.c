#include "vga.h"

void kmain() {
    vga_clear_screen();
    vga_print("Deepak OS Booted Successfully!\n", 0x0F);
    vga_print("Welcome to Deepak OS!\n", 0x0A);

    while (1);
}
