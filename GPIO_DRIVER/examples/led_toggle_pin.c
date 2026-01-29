#include "gpio_driver.h"

/*
 * Example : Toggle LED pin using GPIO driver
 * MCU     : ATmega2560
 * Driver  : Custom GPIO HAL (MCAL-style)
 *
 * LED is connected to PORTA PIN1
 */

int main(void)
{
    // Configure PORTA PIN1 as OUTPUT 
    gpio_init_pin(GPIO_PORT_A, GPIO_PIN_1, GPIO_OUTPUT);

    while (1)
    {
        // Toggle LED 
        gpio_toggle_pin(GPIO_PORT_A, GPIO_PIN_1);

        // Simple software delay 
        for (volatile uint32_t i = 0; i < 500000; i++)
        {
            // delay 
        }
    }
}