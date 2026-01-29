#include "gpio_driver.h"

/*
 * Example : Read GPIO pin and control LED
 * MCU     : ATmega2560
 * Driver  : Custom GPIO HAL (MCAL-style)
 *
 * Button  : PORTD PIN2
 * LED     : PORTB PIN0
 */

int main(void)
{
    // Configure LED pin as OUTPUT
    gpio_init_pin(GPIO_PORT_B, GPIO_PIN_0, GPIO_OUTPUT);

    // Configure Button pin as INPUT
    gpio_init_pin(GPIO_PORT_D, GPIO_PIN_2, GPIO_INPUT);

    while (1)
    {
        // Read button state
        uint8_t button_state = gpio_read_pin(GPIO_PORT_D, GPIO_PIN_2);

        if (button_state)
        {
            // Turn ON LED
            gpio_write_pin(GPIO_PORT_B, GPIO_PIN_0, GPIO_HIGH);
        }
        else
        {
            // Turn OFF LED
            gpio_write_pin(GPIO_PORT_B, GPIO_PIN_0, GPIO_LOW);
        }
    }
}
