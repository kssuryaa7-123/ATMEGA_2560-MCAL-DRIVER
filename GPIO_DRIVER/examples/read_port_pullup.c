#include "gpio_driver.h"

/*
 * Example : Read GPIO port with internal pull-ups enabled
 * MCU     : ATmega2560
 *
 * PORTD is connected to buttons (active LOW)
 */

int main(void)
{
    uint8_t button_state;

    // Configure PORTD as INPUT
    gpio_init_port(GPIO_PORT_D, GPIO_INPUT);

    // Enable internal pull-ups for entire PORTD
    gpio_enable_pullup_port(GPIO_PORT_D);

    while (1)
    {
        // Read button states
        button_state = gpio_read_port(GPIO_PORT_D);

        // Button pressed → corresponding bit = 0
    }
}
