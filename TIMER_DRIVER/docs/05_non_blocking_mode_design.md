# 05. Non-Blocking Mode Design

## 1. Design Objective

Non-blocking mode provides interrupt-driven delay generation while preserving full CPU availability.

Unlike blocking mode, the processor does not wait for delay completion.  
Execution continues independently while the timer operates in hardware.

This mode is engineered to:

- Preserve CPU resources
- Enable concurrent execution
- Provide deterministic callback triggering
- Support scalable multi-cycle delays
- Maintain strict control over hardware activation

The timer does not auto-start during configuration.

Execution is explicitly controlled by API calls.

---

## 2. Architectural Control Model

Non-blocking mode follows a four-stage control model:

1. Initialization
2. Start
3. Stop
4. Deinitialization

Each stage has a clearly defined responsibility.

No stage overlaps with another.

This ensures deterministic behavior and predictable hardware control.

---

## 3. Initialization Phase — `TIMER_INIT()`

Initialization performs configuration only.

During this phase:

- Delay value is normalized
- Prescaler is selected analytically
- Required tick count is computed
- Multi-cycle decomposition is performed
- OCR value is derived
- Configuration is stored in the non-blocking handle
- TIMER3 is configured in CTC mode
- Interrupt mask is prepared (but execution not yet started)
- Counter register is reset
- callback function initialized

Important:

The timer is not started during initialization.

Prescaler bits are not enabled yet.

This guarantees zero unintended execution.

Initialization prepares the timing engine.
It does not activate it.

---

## 4. Start Phase — `TIMER_START()`

`TIMER_START()` activates hardware execution.

During this phase:

- TCNT3 is reset to ensure clean start boundary
- Compare interrupt is enabled
- Prescaler bits are set
- Global interrupts are enabled (if required)

At this moment:

- TIMER3 begins counting
- Interrupt-driven execution starts
- CPU continues normal execution

Since all parameters were precomputed during initialization:

- No runtime configuration latency occurs
- No tick recalculation is performed
- Execution begins immediately with finalized values

---

## 5. Stop Phase — `TIMER_STOP()`

`TIMER_STOP()` halts timer execution without destroying configuration.

During this phase:

- Prescaler bits are cleared
- Compare interrupt is disabled
- Timer counting stops immediately

The handle remains intact.

This allows controlled pause behavior without reinitialization.

The timer can be restarted deterministically using `TIMER_START()`.

---

## 6. Deinitialization Phase — `TIMER_DEINIT()`

`TIMER_DEINIT()` performs full system cleanup.

During this phase:

- Prescaler bits cleared
- Compare interrupt disabled
- Timer registers reset
- OCR register cleared
- TCNT3 reset
- Internal handle state reset
- Callback pointer cleared

After deinitialization:

- No residual hardware state remains
- No background interrupt is active
- Handle state returns to default

This ensures safe reuse and hardware integrity.

---

## 7. Timer Allocation Strategy

Non-blocking mode exclusively uses:

→ **TIMER3 (16-bit)**

Rationale:

- Extended delay capacity
- ISR vector isolation
- No interference with blocking mode
- Scalable multi-cycle handling
- Resource-aware allocation

This prevents cross-mode timing conflicts.

---

## 8. Interrupt Service Routine Design

ISR: `TIMER3_COMPA_vect`

The ISR performs minimal deterministic operations:

- Decrement cycle counter
- Switch to partial OCR if required
- Detect final cycle completion
- Stop timer automatically upon completion
- Execute callback function

The ISR avoids:

- Runtime mathematical calculations
- Floating-point operations
- Configuration decisions
- Heavy logic

This ensures:

- Low interrupt latency
- Predictable execution
- Stable system responsiveness

The ISR acts as a cycle-state controller.

---

## 9. Multi-Cycle Delay Handling

If required ticks exceed 65536:

The delay is decomposed into:

- Full cycles (OCR = 65535)
- Final partial cycle

The ISR manages cycle transitions deterministically.

This allows delay generation beyond single 16-bit overflow capacity without modifying hardware constraints.

---

## 10. Deterministic Timing Model

Tick calculation:

ticks = (delay_us × 16.0) / prescaler

For non-blocking mode:

→ round() is applied

All timing parameters are finalized during initialization.

No recalculation occurs during start or interrupt execution.

This prevents drift accumulation and ensures stable callback timing.

---

## 11. Callback Abstraction

The user provides:

void (*callback)(void);

The callback executes only after final cycle completion.

The driver guarantees timing precision.
The application defines post-delay behavior.

This maintains separation between timing control and functional logic.

---

## 12. Engineering Characteristics

This implementation demonstrates:

- Hardware-first analytical derivation
- Explicit execution control via API
- Deterministic interrupt-driven timing
- Zero runtime configuration latency
- Structured handle abstraction
- Multi-cycle scalability
- Clean hardware reset discipline

Non-blocking mode is not merely interrupt usage.

It is a controlled, state-driven timing subsystem with explicit lifecycle management.

---

This completes the non-blocking mode architecture aligned with the driver control model.
