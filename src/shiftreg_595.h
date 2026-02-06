#pragma once
#include <stdint.h>
#include <stddef.h>

// Initialize GPIOs used to drive the 74HC595 shift register chain.
// Sets pin directions and safe initial states.
void shiftreg_595_init(void);

// Shift out 8 bits and latch them to outputs.
// Bit order: LSB first (bit 0 shifted first)
void shiftreg_595_write_u8(uint8_t value);

void shiftreg_595_write_bytes(const uint8_t *bytes, size_t len);
