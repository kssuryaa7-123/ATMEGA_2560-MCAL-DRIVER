#include "gpio_driver.h"

/*
 * Example : Button input(pin) using internal pull-up resistor
 * MCU     : ATmega2560
 * Driver  : Custom GPIO HAL (MCAL-style)
 *
 * Button  : PORTD PIN2 (connected to GND when pressed)
 * LED     : PORTB PIN0
 */

int main(void)
{
    // Configure LED pin as OUTPUT
    gpio_init_pin(GPIO_PORT_B, GPIO_PIN_0, GPIO_OUTPUT);

    // Enable internal pull-up on button pin
    gpio_enable_pullup_pin(GPIO_PORT_D, GPIO_PIN_2);

    while (1)
    {
        // Button pressed -> pin reads LOW (0)
        if (gpio_read_pin(GPIO_PORT_D, GPIO_PIN_2) == 0)
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
