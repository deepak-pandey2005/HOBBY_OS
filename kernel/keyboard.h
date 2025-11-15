#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

// Initialize keyboard (if needed for IRQ or PS/2)
void kbd_init(void);

// Get a key press (polling version)
// Returns 0 if no key pressed, or ASCII character
char kbd_get_char(void);

// Optional: low-level scan code reading (for advanced use)
uint8_t kbd_read_scancode(void);

#endif
