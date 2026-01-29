# ATmega2560 MCAL / HAL-Style Driver Library

## Overview
This repository provides a collection of reusable, MCAL-style peripheral
drivers for the **ATmega2560** microcontroller, written in **bare-metal C**
with a strong focus on clean architecture, modularity, and maintainability.

The design philosophy is inspired by **STM32 HAL / MCAL concepts**, adapted
carefully for an **8-bit AVR platform**, enabling structured and professional
firmware development without relying on the Arduino framework.

Each peripheral is implemented as an independent driver module with its
own source files, examples, and dedicated documentation.

---

## Key Features
- MCAL-style layered driver architecture
- Peripheral-wise modular design
- Clean, high-level APIs abstracting hardware registers
- Bare-metal implementation (no Arduino dependencies)
- Easy to scale and extend with new peripherals
- Well-documented and example-driven learning approach

---

## Supported Microcontroller
- **ATmega2560**
- Architecture: AVR 8-bit
- Toolchain: AVR-GCC compatible

---

## Repository Structure

Each peripheral is placed in its **own folder**, following a consistent
and reusable structure.

 ATMEGA2560_MCAL_DRIVERS/
- │
- ├── gpio_driver/
- │ ├── inc/ # GPIO driver header files
- │ ├── src/ # GPIO driver source files
- │ ├── examples/ # GPIO usage examples
- │ ├── GPIO_README.md
- │
- ├── LICENSE
- └── README.md # This file


>  **Important:**  
> Every peripheral folder contains its own README file explaining:
> - API design
> - Driver usage
> - Example applications
> - Hardware behavior and notes

---

## Available Drivers

### GPIO Driver
The GPIO driver provides pin-level and port-level control with support
for internal pull-up resistors and clean HAL-style APIs.

- Location: `gpio_driver/`  
- Documentation: `gpio_driver/GPIO_README.md`

---

## How to Use This Repository
1. Clone or download the repository
2. Navigate to the required peripheral folder
3. Read the peripheral-specific README file
4. Use the provided examples as a reference
5. Integrate the driver into your application code

This structure keeps the repository clean while allowing each driver
to be understood independently.

---

## Design Philosophy
- Register-level complexity is hidden behind driver APIs
- Application code remains portable and readable
- Drivers follow MCAL principles used in automotive and STM32 ecosystems
- Code is written for **clarity first**, then efficiency

---

## License
See the `LICENSE` file.  
You are free to **view and use** this code, but **cannot modify the main repository**.
Please give proper credit to **Jeya Suryaa Ks** if you use this work.

---

## Author
Jeya Suryaa Ks 
|Embedded Systems | Bare-Metal Firmware | Driver Development
