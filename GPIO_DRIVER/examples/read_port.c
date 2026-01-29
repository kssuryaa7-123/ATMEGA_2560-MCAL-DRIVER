#include "gpio_driver.h"

/*
 * Example : Read entire GPIO port
 * MCU     : ATmega2560
 *
 * PORTA is connected to 8 switches / inputs
 */

int main(void)
{
    uint8_t port_value;

    // Configure entire PORTA as INPUT
    gpio_init_port(GPIO_PORT_A, GPIO_INPUT);

    while (1)
    {
        // Read entire port
        port_value = gpio_read_port(GPIO_PORT_A);

        // Use port_value for application logic
        // (debug, decision making, etc.)
    }
}
