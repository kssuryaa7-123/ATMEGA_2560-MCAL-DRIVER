#include "gpio_driver.h"

/*
 * Example: Turn ON ALL LED connected to PORTA
 * MCU     : ATmega2560
 * Driver  : Custom GPIO HAL (bare-metal)
 */

int main(void)
{
    // Configure PORTA  as OUTPUT 
    gpio_init_port(GPIO_PORT_A, GPIO_OUTPUT);

    // Set PORTA PIN1 HIGH (LED ON) */
    gpio_write_port(GPIO_PORT_A, GPIO_HIGH);

    while (1)
    {
        // Infinite loop – LED remains ON 
    }
}
