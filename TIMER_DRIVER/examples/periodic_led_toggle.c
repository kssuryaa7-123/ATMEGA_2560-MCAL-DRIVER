#include "gpio_driver.h"
#include "timer_driver.h"

/*
 * Example: Non-blocking periodic LED toggle
 * MCU     : ATmega2560
 * Driver  : Custom Timer HAL (bare-metal)
 */

// Callback function executed inside Timer ISR
void toggleled(void)
{
    gpio_toggle_pin(GPIO_PORT_A, GPIO_PIN_1);
}

int main(void)
{
    // Configure LED pin as OUTPUT
    gpio_init_pin(GPIO_PORT_A, GPIO_PIN_1, GPIO_OUTPUT);

    // Initialize non-blocking timer (1 second period)
    TIMER_INIT(1, SEC, toggleled);

    // Start timer
    TIMER_START();

    while (1)
    {
        // Main loop remains free
        // Non-blocking execution
    }
}
