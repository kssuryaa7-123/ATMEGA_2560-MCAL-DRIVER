# 02. Architecture Design

## Design Philosophy

The Timer Driver is architected using a layered MCAL-style design model to ensure deterministic behavior, clean hardware abstraction, and long-term scalability.

Rather than embedding mathematical computation, configuration logic, and register manipulation inside a single function, the driver strictly separates responsibilities across defined layers.

This architecture reflects professional embedded firmware practices where:

- Hardware interaction is isolated  
- Configuration is data-driven  
- Mathematical derivation is independent of register access  
- System behavior remains predictable and testable  

The design is analytical, not empirical.  
All configuration decisions are derived from hardware constraints and mathematical relationships — not trial-and-error tuning.

---

## Layered Architecture Overview

The driver follows the structured hierarchy below:

-  Application Layer
-        ↓
- HAL Calculation Layer
-        ↓
- Timer Handle Abstraction
-        ↓
-   MCAL Timer Driver
-        ↓
- AVR Hardware Registers


Each layer has a single, clearly defined responsibility.  
No layer violates the responsibility of another.

This strict separation ensures deterministic behavior, simplified debugging, and long-term maintainability.

---

## 1. Application Layer

This layer exposes the public APIs:

- `timer_delay()`
- `TIMER_INIT()`
- `TIMER_START()`
- `TIMER_STOP()`
- `TIMER_DEINIT()`

The application interacts only with these interfaces.

It does not:
- Access hardware registers  
- Perform mathematical calculations  
- Manage prescalers  

This guarantees full hardware abstraction from user-level logic.

The application expresses *intent* only.  
The driver determines *execution*.

---

## 2. HAL Calculation Layer

This layer performs all mathematical derivation required for timer configuration.

Responsibilities include:

- Normalizing user time input into microseconds  
- Calculating total required timer ticks  
- Selecting the smallest valid prescaler  
- Determining whether 8-bit or 16-bit timer is required  
- Computing OCR values using deterministic rounding policy  
- Decomposing large delays into multiple hardware cycles  

This layer does **not** write to hardware registers.

It prepares configuration data only.

By isolating mathematical computation here:

- The design becomes testable without hardware  
- Timing derivations remain transparent  
- Future clock changes require modification in only one location  
- Configuration remains analytically derived  

This reflects disciplined firmware engineering practice.

---

## 3. Timer Handle Abstraction

All configuration results are stored inside structured timer handle objects.

Two independent handles are maintained:

- Blocking mode handle  
- Non-blocking mode handle  

Each handle stores:

- Selected timer type (8-bit / 16-bit)  
- Prescaler value  
- OCR value  
- Full cycle count  
- Partial cycle information  
- Callback function pointer (non-blocking mode)  

This abstraction creates a clean boundary between configuration logic and hardware execution.

The MCAL layer consumes this structured data without recalculating or reinterpreting it.

This model improves maintainability and ensures scalability for future extensions.

---

## 4. MCAL Timer Driver Layer

The MCAL layer performs direct hardware register manipulation.

Responsibilities include:

- Configuring CTC mode  
- Writing OCR values  
- Setting prescaler bits  
- Resetting timer registers  
- Enabling or disabling interrupt masks  
- Starting and stopping hardware timers  

This layer performs **no mathematical calculations**.

It strictly applies configuration parameters received from the handle abstraction.

By keeping the MCAL layer purely hardware-oriented:

- Register access remains controlled  
- Hardware side effects are localized  
- Porting to another MCU becomes simpler  

---

## 5. Hardware Layer

The lowest layer consists of AVR hardware registers:

- `TCCRnA / TCCRnB`  
- `OCRn`  
- `TIMSKn`  
- `TCNTn`  

All access to these registers is mediated through the MCAL layer.

The upper layers remain completely hardware-independent.

---

## Architectural Strengths

This architecture provides:

- Strict separation of concerns  
- Deterministic configuration flow  
- Clean abstraction between math and hardware  
- Improved debugging capability  
- Resource-aware timer selection  
- Scalable multi-cycle delay handling  
- Hardware-first analytical derivation  
- Deterministic-by-design configuration  
- Resource preservation strategy  
- Long-term portability  

The structure mirrors industry-aligned firmware layering principles used in professional embedded systems.

Future enhancements — such as additional timers, clock modifications, new operating modes, or platform migration — can be implemented with minimal impact on higher layers.
