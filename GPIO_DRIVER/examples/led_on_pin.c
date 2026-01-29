#include "gpio_driver.h"

/*
 * Example: Turn ON an LED connected to PORTA PIN1
 * MCU     : ATmega2560
 * Driver  : Custom GPIO HAL (bare-metal)
 */

int main(void)
{
    // Configure PORTA PIN1 as OUTPUT
    gpio_init_pin(GPIO_PORT_A, GPIO_PIN_1, GPIO_OUTPUT);

    // Set PORTA PIN1 HIGH (LED ON) 
    gpio_write_pin(GPIO_PORT_A, GPIO_PIN_1, GPIO_HIGH);

    while (1)
    {
        // Infinite loop – LED remains ON 
    }
}
