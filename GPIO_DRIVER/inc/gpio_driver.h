
#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>

// ===============================
// GPIO Logic Level Definition...
// ===============================
typedef enum
{
    GPIO_LOW  = 0U,   // Logic LOW 
    GPIO_HIGH = 1U    // Logic HIGH 
} gpio_state_t;


// ==================================
// GPIO Direction Mode Definition...
// ==================================
typedef enum
{
    GPIO_INPUT  = 0U, // Configure pin as input
    GPIO_OUTPUT = 1U  // Configure pin as output 
} gpio_mode_t;


// ===============================
// GPIO Pin Number Definition...
// ===============================
typedef enum
{
    GPIO_PIN_0 = 0U,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7
} gpio_pin_t;


// ======================================
// GPIO Register Definition Structure...
// ======================================
typedef struct
{
    volatile uint8_t PIN;   // Input Pins Address 
    volatile uint8_t DDR;   // Data Direction Register 
    volatile uint8_t PORT;  // Data Register 
} gpio_regdef_t;


// =========================================
// GPIO Port Base Addresses (ATmega2560)...
// =========================================
#define GPIO_PORT_A   ((gpio_regdef_t*)0x20)
#define GPIO_PORT_B   ((gpio_regdef_t*)0x23)
#define GPIO_PORT_C   ((gpio_regdef_t*)0x26)
#define GPIO_PORT_D   ((gpio_regdef_t*)0x29)
#define GPIO_PORT_E   ((gpio_regdef_t*)0x2C)
#define GPIO_PORT_F   ((gpio_regdef_t*)0x2F)
#define GPIO_PORT_G   ((gpio_regdef_t*)0x32)
#define GPIO_PORT_H   ((gpio_regdef_t*)0x100)
#define GPIO_PORT_J   ((gpio_regdef_t*)0x103)
#define GPIO_PORT_K   ((gpio_regdef_t*)0x106)
#define GPIO_PORT_L   ((gpio_regdef_t*)0x109)


// ============================
// GPIO HAL API (FUNCTIONS)...
 // ===========================

// Initialize a specific GPIO pin.. 
void gpio_init_pin(gpio_regdef_t *port, gpio_pin_t pin, gpio_mode_t mode);

// Initialize an entire GPIO port.. 
void gpio_init_port(gpio_regdef_t *port, gpio_mode_t mode);

// Write logic level to a GPIO pin..
void gpio_write_pin(gpio_regdef_t *port, gpio_pin_t pin, gpio_state_t state);

// Write logic level to an entire GPIO port.. 
void gpio_write_port(gpio_regdef_t *port, gpio_state_t state);

// Read logic level from a GPIO pin..
uint8_t gpio_read_pin(gpio_regdef_t *port, gpio_pin_t pin);

// Read value of an entire GPIO port..
uint8_t gpio_read_port(gpio_regdef_t *port);

// Toggle a GPIO pin..
void gpio_toggle_pin(gpio_regdef_t *port, gpio_pin_t pin);

// Toggle an entire GPIO port ..
void gpio_toggle_port(gpio_regdef_t *port);

// Enable internal pull-up resistor for a specific GPIO pin..
void gpio_enable_pullup_pin(gpio_regdef_t *port, gpio_pin_t pin);

// Disable internal pull-up resistor for a specific GPIO pin..
void gpio_disable_pullup_pin(gpio_regdef_t *port, gpio_pin_t pin);

// Enable internal pull-up resistors for an entire GPIO port..
void gpio_enable_pullup_port(gpio_regdef_t *port);

// Disable internal pull-up resistors for an entire GPIO port..
void gpio_disable_pullup_port(gpio_regdef_t *port);

#endif // GPIO_DRIVER_H

