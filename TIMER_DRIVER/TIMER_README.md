# ATmega2560 Timer Driver (MCAL / HAL-Style)

## Overview
This project implements a reusable MCAL-style Timer driver for the  
ATmega2560 microcontroller using bare-metal C programming.

The driver provides hardware-based timing services using AVR timers,
supporting both blocking delays and non-blocking periodic execution
through interrupt-driven callbacks.

The design is inspired by STM32 HAL Timer concepts and follows a clean,
layered architecture suitable for scalable embedded applications on
8-bit AVR platforms.

---

## Key Highlights
- MCAL-style layered timer driver design  
- STM32 HAL-inspired Timer APIs  
- Hardware-based blocking delay support  
- Non-blocking timer with callback mechanism  
- ISR-driven periodic execution  
- Bare-metal implementation (no Arduino delay APIs)  
- Clean separation between hardware, driver, and application layers  

---

## Supported MCU
- ATmega2560  
- Architecture: AVR 8-bit  

---

## Folder Structure

- TIMER_DRIVER  
- │  
- ├── docs/         # Design & implementation documentation  
- ├── examples/     # Usage examples  
- ├── inc/          # Timer driver headers  
- ├── src/          # Timer driver implementation   
- ├── README.md     # Documentation  

---

## Demo Video

A complete working demonstration of the ATmega2560 Timer Driver  
(Blocking + Non-Blocking execution) is available below:

[Download / Watch Demo Video](docs/demo.mp4)

> ⚠️ Note: GitHub cannot play the video inline. Please use the link above to download and   watch the demo locally.

### What the demo covers:
- Hardware-based blocking delay execution  
- Interrupt-driven non-blocking periodic callback  
- Parallel execution behavior validation  
- Deterministic timer operation  

---



## Timer HAL APIs

### Blocking Delay API
- `timer_delay()`

### Non-Blocking Timer APIs
- `TIMER_INIT()`  
- `TIMER_START()`  
- `TIMER_STOP()`  
- `TIMER_DEINIT()`  

---

## API Behavior Overview

### Blocking Timer Mode
#### Description
- Uses hardware timer configured in CTC mode  
- Execution halts until the configured delay expires  
- Suitable for simple and deterministic timing requirements  

#### Typical Use-Cases
- Startup delays  
- Sensor stabilization delays  
- Short timing gaps in linear execution flow  

---

### Non-Blocking Timer Mode
#### Description
- Configures a periodic hardware timer  
- Executes a user-defined callback function  
- Callback is invoked from the Timer ISR  
- Main application execution remains non-blocking  

#### Callback Execution Rules
- Callback executes in interrupt context  
- Keep callback code short and deterministic  
- Avoid delays, blocking calls, or heavy computations  

---

## Example Application

All example files are located inside the `examples/` folder and  
demonstrate one specific timer use-case per file for clarity and  
learning purposes.


### Blocking Timer Example  
- #### Hardware Delay

`blocking_delay.c`  
→ Generate a hardware-based blocking delay

---

### Non-Blocking Timer Examples  

- #### Periodic Execution

`periodic_led_toggle.c`  
→ Toggle an LED periodically using timer callback

- #### Runtime Control

`timer_start_stop.c`  
→ Start and stop a non-blocking timer dynamically during runtime

- #### Reinitialization & Callback Update

`timer_reinitialize_callback.c`  
→ Deinitialize the timer and reinitialize it with a new callback and timing configuration

---


## Documentation
#### Internal Design & Implementation

Detailed explanations of:
- Timer design architecture diagram  
- CTC mode configuration  
- Blocking vs non-blocking design  
- ISR flow and callback execution  
- Driver integration workflow  

are available inside the `docs` folder.

**Highly recommended** for developers who want a deep understanding of
the driver internals and design decisions.

---

## Why This Driver Matters
#### Beyond Basic Timer Usage

This timer driver is intentionally designed to go beyond simple delay
generation.

It demonstrates how:
- Hardware timers can be abstracted cleanly without losing control
- Blocking and non-blocking designs can coexist in a single driver
- ISR-driven callbacks can be integrated safely and predictably
- MCAL concepts used in automotive and STM32 ecosystems can be applied
  to 8-bit AVR microcontrollers

The full design rationale, timer configuration flow, block diagrams,
and implementation details are documented step-by-step inside the
`docs/` folder.

If you are learning **how professional embedded drivers are structured**,
the documentation is where the real value lies.

## Design Philosophy
#### MCAL-Oriented Architecture
- Timer hardware registers are fully abstracted behind driver APIs  
- Application code remains independent of register-level details  
- Clean, reusable, and scalable firmware architecture  
- MCAL principles inspired by automotive and STM32 HAL drivers  

---

## License
See `LICENSE` file.  
You are free to view and use this code, but **cannot modify my main repository**.  
Please credit **Jeya Suryaa Ks** if you use this code.

---

## Author
Jeya Suryaa Ks