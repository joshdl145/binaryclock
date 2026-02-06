#include "shiftreg_595.h"

#include "pico/stdlib.h"
#include "pins.h"

static uint8_t PULSE_WIDTH = 0x01;

static inline void pulse_pin(uint pin)
{
    gpio_put(pin, 1);
    sleep_us(PULSE_WIDTH);
    gpio_put(pin, 0);
    sleep_us(PULSE_WIDTH);
}

static inline void shift_byte_msb_first(uint8_t value) {
    for (int i = 0; i < 8; i++) {
        uint8_t bit_val = (value & 0x80) ? 0x01 : 0x00;
        gpio_put(DS_PIN, bit_val);

        // Pulse she shift clock.
        pulse_pin(SHIFT_CLK_PIN);
        value <<= 1;
    }
}

void shiftreg_595_init(void)
{
    gpio_init(LATCH_PIN);
    gpio_init(SHIFT_CLK_PIN);
    gpio_init(DS_PIN);

    gpio_set_dir(LATCH_PIN, GPIO_OUT);
    gpio_set_dir(SHIFT_CLK_PIN, GPIO_OUT);
    gpio_set_dir(DS_PIN, GPIO_OUT);

    // Set idle states
    gpio_put(LATCH_PIN, 0);
    gpio_put(SHIFT_CLK_PIN, 0);
    gpio_put(DS_PIN, 0);
}

void shiftreg_595_write_bytes(const uint8_t *bytes, size_t len) {
    if (bytes == NULL || len == 0) {
        return;
    }

    // Force the Register Clock to low during bit shifting
    gpio_put(LATCH_PIN, 0);

    for (size_t i = 0; i < len; i++) {
        shift_byte_msb_first(bytes[i]);
    }

    pulse_pin(LATCH_PIN);
}

void shiftreg_595_write_u8(uint8_t value)
{
    // Force the Register Clock to low during bit shifting
    gpio_put(LATCH_PIN, 0);

    shift_byte_msb_first(value);

    // Pulse the Register clock to latch the data
    pulse_pin(LATCH_PIN);
}