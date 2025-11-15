#include "keyboard.h"
#include "vga.h"
#include <stdint.h>

#define KBD_DATA_PORT 0x60

static uint8_t last_scancode = 0;

// Read a byte from I/O port
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// Convert scancode to ASCII (US QWERTY, standard keys)
static char scancode_to_ascii(uint8_t sc) {
    switch(sc) {
        // Numbers
        case 0x02: return '1';
        case 0x03: return '2';
        case 0x04: return '3';
        case 0x05: return '4';
        case 0x06: return '5';
        case 0x07: return '6';
        case 0x08: return '7';
        case 0x09: return '8';
        case 0x0A: return '9';
        case 0x0B: return '0';

        // Letters
        case 0x10: return 'q';
        case 0x11: return 'w';
        case 0x12: return 'e';
        case 0x13: return 'r';
        case 0x14: return 't';
        case 0x15: return 'y';
        case 0x16: return 'u';
        case 0x17: return 'i';
        case 0x18: return 'o';
        case 0x19: return 'p';
        case 0x1E: return 'a';
        case 0x1F: return 's';
        case 0x20: return 'd';
        case 0x21: return 'f';
        case 0x22: return 'g';
        case 0x23: return 'h';
        case 0x24: return 'j';
        case 0x25: return 'k';
        case 0x26: return 'l';
        case 0x2C: return 'z';
        case 0x2D: return 'x';
        case 0x2E: return 'c';
        case 0x2F: return 'v';
        case 0x30: return 'b';
        case 0x31: return 'n';
        case 0x32: return 'm';

        // Symbols
        case 0x0C: return '-';
        case 0x0D: return '=';
        case 0x1A: return '[';
        case 0x1B: return ']';
        case 0x27: return ';';
        case 0x28: return '\'';
        case 0x29: return '`';
        case 0x2B: return '\\';
        case 0x33: return ',';
        case 0x34: return '.';
        case 0x35: return '/';

        // Special keys
        case 0x39: return ' ';  // Space
        case 0x1C: return '\n'; // Enter
        case 0x0E: return '\b'; // Backspace

        default: return 0;
    }
}

// Initialize keyboard (polling)
void kbd_init(void) {
    // nothing needed for polling
}

// Get key from keyboard
char kbd_get_char(void) {
    uint8_t scancode = inb(KBD_DATA_PORT);

    // Ignore key releases (scancode >= 0x80)
    if (scancode & 0x80) {
        last_scancode = 0;
        return 0;
    }

    // Ignore repeated keys
    if (scancode == last_scancode)
        return 0;

    last_scancode = scancode;

    char c = scancode_to_ascii(scancode);
    if (c == 0) return 0;

    return c;
}
