#include "gpio_driver.h"
#include "timer_driver.h"

/*
 * Example: Toggle LED using blocking delay
 * MCU     : ATmega2560
 * Driver  : Custom Timer HAL (bare-metal)
 */

int main(void)
{
    // Configure LED pin as OUTPUT
    gpio_init_pin(GPIO_PORT_A, GPIO_PIN_1, GPIO_OUTPUT);

    while (1)
    {
        // Turn LED ON
        gpio_write_pin(GPIO_PORT_A, GPIO_PIN_1, GPIO_HIGH);

        // Blocking delay: 1 second
        timer_delay(1, SEC);

        // Turn LED OFF
        gpio_write_pin(GPIO_PORT_A, GPIO_PIN_1, GPIO_LOW);

        // Blocking delay: 1 second
        timer_delay(1, SEC);
    }
}
