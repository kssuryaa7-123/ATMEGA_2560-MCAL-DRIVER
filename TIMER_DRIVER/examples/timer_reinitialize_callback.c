#include "gpio_driver.h"
#include "timer_driver.h"

/*
 * Example: Deinitialize and Reinitialize Timer with New Callback
 * MCU     : ATmega2560
 * Driver  : Custom Timer HAL (bare-metal)
 */

// First callback
void toggle_led(void)
{
    gpio_toggle_pin(GPIO_PORT_A, GPIO_PIN_1);
}

// Second callback
void toggle_led_fast(void)
{
    gpio_toggle_pin(GPIO_PORT_A, GPIO_PIN_1);
}

int main(void)
{
    // Configure LED as OUTPUT
    gpio_init_pin(GPIO_PORT_A, GPIO_PIN_1, GPIO_OUTPUT);

    // ----------------------------
    // First Initialization
    // ----------------------------
    TIMER_INIT(1, SEC, toggle_led);
    TIMER_START();

    // Let it run for 5 seconds
    timer_delay(5, SEC);

    // Stop and Deinitialize
    TIMER_STOP();
    TIMER_DEINIT();

    // ----------------------------
    // Reinitialize with new callback
    // ----------------------------
    TIMER_INIT(500, MS, toggle_led_fast);
    TIMER_START();

    while (1)
    {
        // Main loop free
    }
}
