
# ATmega2560 GPIO Driver (MCAL / HAL-Style)

## Overview
This project implements a reusable MCAL-style GPIO driver for the
ATmega2560 microcontroller using bare-metal C programming.

The driver design is inspired by STM32 HAL concepts, providing clean,
high-level APIs that abstract direct register access and promote
portable and maintainable application code on an 8-bit AVR platform.

---

## Key Highlights
- MCAL-style layered driver design
- STM32 HAL-inspired GPIO APIs
- Pin-level and port-level control
- Internal pull-up resistor configuration support
- Bare-metal implementation (no Arduino framework)
- Reusable and scalable firmware architecture

---

## Supported MCU
- ATmega2560
- Architecture: AVR 8-bit

---

## Folder Structure

- GPIO_DRIVER/
- |__inc/ # Driver headers
- |
- |__inc/ # Driver headers
- |
- |__src/ # Driver implementation
- |
- |__examples/ # Usage examples
- |
- |__LICENSE # License info
- |
- |__GPIO_README.md # Documentation
              
---

## GPIO HAL APIs

### Initialization
- `gpio_init_pin()`
- `gpio_init_port()`

### Write Operations
- `gpio_write_pin()`
- `gpio_write_port()`

### Read Operations
- `gpio_read_pin()`
- `gpio_read_port()`

### Toggle Operations
- `gpio_toggle_pin()`
- `gpio_toggle_port()`

### Pull-up Resistor Control
- `gpio_enable_pullup_pin()`
- `gpio_disable_pullup_pin()`
- `gpio_enable_pullup_port()`
- `gpio_disable_pullup_port()`

Note:
Internal pull-up resistors are enabled by configuring the pin as
input (DDR = 0) and setting the corresponding PORT bit, following
AVR hardware specifications.pullup functions does this.

---

## Example Application
All example files are located inside the examples/ folder and demonstrate
one specific GPIO use-case per file for clarity and learning purposes.

### Output Control Examples

`led_on_pin.c`
→ Turn ON an LED using a single GPIO pin

`led_on_port.c`
→ Drive an entire GPIO port as output

`led_toggle_pin.c`
→ Toggle a single GPIO pin

`led_toggle_port.c`
→ Toggle all pins of a GPIO port

### Read Operation Examples (Without Pull-up)

`read_pin_led.c`
→ Read the logic level of an input pin (external drive assumed)

`read_port.c`
→ Read the value of an entire GPIO port

- Read Operation Examples (With Internal Pull-up)

`readpin_button_pullup.c`
→ Read a push-button input using internal pull-up resistor

`read_port_pullup.c`
→ Read an entire GPIO port with internal pull-ups enabled

**Note:**  
The `gpio_disable_pullup_*()` APIs are fully functional and are intended
for **runtime control** of internal pull-up resistors.

They are not explicitly used in the example files because each example
demonstrates a fixed and focused GPIO use-case. In real applications,
these APIs can be used dynamically to enable or disable pull-ups based
on system state, power requirements, or input mode changes during
program execution.


---

## Design Philosophy
- Hardware registers are abstracted through driver APIs
- Application code remains independent of register-level details,clean reusable APIs
- Driver structure follows MCAL principles commonly used in
  automotive and STM32-based embedded systems

---

## License
See `LICENSE` file.  
You are free to view and use this code, but **cannot not modify my main repository**. Please credit **Jeya Suryaa Ks** if you use this code.

---

## Author
Jeya Suryaa Ks