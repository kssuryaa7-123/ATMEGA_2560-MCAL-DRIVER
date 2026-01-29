#include "gpio_driver.h"

/*
 * Example : Toggle entire GPIO port
 * MCU     : ATmega2560
 * Driver  : Custom GPIO HAL (MCAL-style)
 *
 * All LEDs are connected to PORTB (PIN0–PIN7)
 */

int main(void)
{
    // Configure entire PORTB as OUTPUT 
    gpio_init_port(GPIO_PORT_B, GPIO_OUTPUT);

    while (1)
    {
        // Toggle all pins of PORTB 
        gpio_toggle_port(GPIO_PORT_B);

        // Simple software delay 
        for (volatile uint32_t i = 0; i < 500000; i++)
        {
            // delay
        }
    }
}
