
/*
 * File   : gpio_driver.c
 * Brief  : MCAL-style GPIO driver implementation for ATmega2560
 *
 * This file provides pin-level and port-level GPIO control APIs.
 * The driver abstracts direct register access and follows a
 * layered MCAL / HAL-inspired design for bare-metal AVR systems.
 */

#include "gpio_driver.h"

/*----------------------------------------------------------
 * Function : gpio_init_pin
 * Purpose  : Configure direction of a single GPIO pin
 * Input    : port - GPIO port base address
 *            pin  - Pin number (PIN_0 to PIN_7)
 *            mode - GPIO_INPUT or GPIO_OUTPUT
 *----------------------------------------------------------*/
void gpio_init_pin(gpio_regdef_t* port, gpio_pin_t pin, gpio_mode_t mode)
{
    if (mode == GPIO_INPUT)
    {
        port->DDR &= ~(1 << pin);// set the direction register as input..
    }
    else
    {
        port->DDR |= (1 << pin);// set the direction register as output..
    }
}


/*----------------------------------------------------------
 * Function : gpio_init_port
 * Purpose  : Configure direction of all GPIO pins in a port
 * Input    : port - GPIO port base address
 *            mode - GPIO_INPUT or GPIO_OUTPUT
 *----------------------------------------------------------*/
void gpio_init_port(gpio_regdef_t* port, gpio_mode_t mode)
{
    if (mode == GPIO_INPUT)
    {
        port->DDR = 0x00;// set the  whole direction register of the port as input..
    }
    else
    {
        port->DDR = 0xFF;// set the  whole direction register of the port as output..
    }
}


/*----------------------------------------------------------
 * Function : gpio_write_pin
 * Purpose  : Write logic level to a GPIO pin
 * Input    : port  - GPIO port base address
 *            pin   - Pin number
 *            state - GPIO_LOW or GPIO_HIGH
 *----------------------------------------------------------*/
void gpio_write_pin(gpio_regdef_t* port, gpio_pin_t pin, gpio_state_t state)
{
    if (state == GPIO_LOW)
    {
        port->PORT &= ~(1 << pin);//set pin value as low.
    }
    else
    {
        port->PORT |= (1 << pin);//set pin value as high.
    }
}


/*----------------------------------------------------------
 * Function : gpio_write_port
 * Purpose  : Write logic level to all pins of a GPIO port
 * Input    : port  - GPIO port base address
 *            state - GPIO_LOW or GPIO_HIGH
 *----------------------------------------------------------*/
void gpio_write_port(gpio_regdef_t* port, gpio_state_t state)
{
    if (state == GPIO_LOW)
    {
        port->PORT = 0x00;//set whole port pin value as low.
    }
    else
    {
        port->PORT = 0xFF;//set whole port pin value as high.
    }
}


/*------------------------------------------
 * Function : gpio_read_pin
 * Purpose  : Read logic level of a GPIO pin
 * Input    : port - GPIO port base address
 *            pin  - Pin number
 * Return   : 0 if LOW, 1 if HIGH
 *------------------------------------------*/
uint8_t gpio_read_pin(gpio_regdef_t* port, gpio_pin_t pin)
{
    return (port->PIN >> pin) & 0x01;
}


/*----------------------------------------------------------
 * Function : gpio_read_port
 * Purpose  : Read logic levels of all pins in a GPIO port
 * Input    : port - GPIO port base address
 * Return   : 8-bit value representing port input state
 *----------------------------------------------------------*/
uint8_t gpio_read_port(gpio_regdef_t* port)
{
    return port->PIN;
}


/*----------------------------------------------------------
 * Function : gpio_toggle_pin
 * Purpose  : Toggle output state of a GPIO pin
 * Input    : port - GPIO port base address
 *            pin  - Pin number
 *----------------------------------------------------------*/
void gpio_toggle_pin(gpio_regdef_t* port, gpio_pin_t pin)
{
    port->PORT ^= (1 << pin);// toogle the specific pin in the port...
}



/*----------------------------------------------------------
 * Function : gpio_toggle_port
 * Purpose  : Toggle output state of all GPIO pins in a port
 * Input    : port - GPIO port base address
 *----------------------------------------------------------*/
void gpio_toggle_port(gpio_regdef_t* port)
{
    port->PORT ^= 0xFF;//toggle the entire port...
}


/*----------------------------------------------------------
 * Function : gpio_enable_pullup_pin
 * Purpose  : Enable internal pull-up resistor for a GPIO pin
 * Input    : port - GPIO port base address
 *            pin  - Pin number
 * Note     : Pin must be configured as INPUT
 *----------------------------------------------------------*/
void gpio_enable_pullup_pin(gpio_regdef_t *port, gpio_pin_t pin)
{
    port->DDR  &= ~(1 << pin);   // Ensure pin is INPUT
    port->PORT |=  (1 << pin);   // Enable pull-up
}


/*----------------------------------------------------------
 * Function : gpio_disable_pullup_pin
 * Purpose  : Disable internal pull-up resistor for a GPIO pin
 * Input    : port - GPIO port base address
 *            pin  - Pin number
 *----------------------------------------------------------*/
void gpio_disable_pullup_pin(gpio_regdef_t *port, gpio_pin_t pin)
{
    port->DDR  &= ~(1 << pin);   // Ensure pin is INPUT
    port->PORT &= ~(1 << pin);   // Disable pull-up
}


/*----------------------------------------------------------
 * Function : gpio_enable_pullup_port
 * Purpose  : Enable internal pull-up resistors for all pins
 * Input    : port - GPIO port base address
 *----------------------------------------------------------*/
void gpio_enable_pullup_port(gpio_regdef_t *port)
{
    port->DDR  = 0x00;   // Configure entire port as INPUT
    port->PORT = 0xFF;   // Enable pull-ups on all pins
}


/*----------------------------------------------------------
 * Function : gpio_disable_pullup_port
 * Purpose  : Disable internal pull-up resistors for all pins
 * Input    : port - GPIO port base address
 *----------------------------------------------------------*/
void gpio_disable_pullup_port(gpio_regdef_t *port)
{
    port->DDR  = 0x00;   // Configure entire port as INPUT
    port->PORT = 0x00;   // Disable pull-ups on all pins
}

