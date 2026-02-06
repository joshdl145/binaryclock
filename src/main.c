#include "pico/stdlib.h"
#include "shiftreg_595.h"

static uint8_t CURRENT_TICK = 0x00;

int main() {
    //Init shift register Pins and GPIO
    shiftreg_595_init();

    while (true) {

        for(int i = 0; i < 5; i++) {
            CURRENT_TICK |= (uint8_t)(0x01 << i);
            shiftreg_595_write_u8(CURRENT_TICK);
            sleep_ms(200);
        }

        for(int i = 5; i-- > 0;) {
            CURRENT_TICK &= ~(uint8_t)(0x01 << i);
            shiftreg_595_write_u8(CURRENT_TICK);
            sleep_ms(200);
        }

        sleep_ms(500);
    }
}