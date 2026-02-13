#include "gpio_driver.h"
#include "timer_driver.h"

/*
 * Example: Start and Stop non-blocking timer dynamically
 * MCU     : ATmega2560
 * Driver  : Custom Timer HAL (bare-metal)
 */

// user written call back function.
void toggleled(void)
{
    gpio_toggle_pin(GPIO_PORT_A, GPIO_PIN_1);
}

int main(void)
{
    gpio_init_pin(GPIO_PORT_A, GPIO_PIN_1, GPIO_OUTPUT);

    // Initialize timer (1 second periodic callback)
    TIMER_INIT(1, SEC, toggleled);

    // Start timer
    TIMER_START();

    while (1)
    {
        // Let LED toggle for 5 seconds
        timer_delay(5, SEC);

        // Stop periodic toggling
        TIMER_STOP();

        // LED remains steady for 3 seconds
        timer_delay(3, SEC);

        // Restart periodic toggling
        TIMER_START();
    }
}
