#pragma once

// Pin assignments for Binary Clock shift-register bus (SN74HC595-style)

#include "stdint.h"

// Fail fast if the build system didn't provide these.
#ifndef BINARY_CLOCK_LATCH_PIN
#error "BINARY_CLOCK_LATCH_PIN is not defined. Set it via target_compile_definitions() in CMake."
#endif

#ifndef BINARY_CLOCK_SHIFT_CLK_PIN
#error "BINARY_CLOCK_SHIFT_CLK_PIN is not defined. Set it via target_compile_definitions() in CMake."
#endif

#ifndef BINARY_CLOCK_DS_PIN
#error "BINARY_CLOCK_DS_PIN is not defined. Set it via target_compile_definitions() in CMake."
#endif

// Shift register bus pins:
// - LATCH: storage register clock (often called RCLK / STCP)
// - SHIFT_CLK: shift register clock (often called SRCLK / SHCP)
// - DS: serial data input (often called SER / DS)
static const uint LATCH_PIN     = BINARY_CLOCK_LATCH_PIN;
static const uint SHIFT_CLK_PIN = BINARY_CLOCK_SHIFT_CLK_PIN;
static const uint DS_PIN        = BINARY_CLOCK_DS_PIN;