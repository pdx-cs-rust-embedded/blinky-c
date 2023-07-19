#include "hardware.h"

extern void delay_loop(unsigned usecs);

void init(void) {
    // Set the LED COL1 pin as low output.
    SET_BIT(GPIO0_DIR, 28);
    CLR_BIT(GPIO0_OUT, 28);

    // Set the LED ROW1 pin as low output.
    SET_BIT(GPIO0_DIR, 21);
    CLR_BIT(GPIO0_OUT, 21);

    while (1) {
        // Set ROW1 pin high.
        SET_BIT(GPIO0_OUT, 21);
        // Wait 0.5 secs.
        delay_loop(500000);
        // Set ROW1 pin low.
        CLR_BIT(GPIO0_OUT, 21);
        // Wait 0.5 secs.
        delay_loop(500000);
    }
}
