# 06. Interrupt Flow Design

## 1. Design Objective

The interrupt flow is responsible for executing the non-blocking timing engine in a deterministic and state-controlled manner.

The ISR does not perform delay computation.  
It does not decide prescaler configuration.  
It does not manage lifecycle control (START/STOP).

Its sole responsibility is controlled cycle progression and callback triggering.

Execution control remains external through API calls.

This preserves architectural discipline and hardware predictability.

---

## 2. Interrupt Ownership Model

Interrupt Vector:

→ `ISR(TIMER3_COMPA_vect)`

Ownership:

- Dedicated exclusively to non-blocking mode
- Isolated from blocking execution
- Bound to TIMER3 in CTC mode

The ISR operates on:

→ `non_block_handle`

This ensures single-source timing state control.

---

## 3. Execution Philosophy

The interrupt flow is designed as a deterministic state machine.

It operates based on three parameters stored inside the handle:

- `cycles`
- `partial_cycle`
- Precomputed OCR values

The ISR does not compute timing.

It transitions between precomputed states.

This ensures:

- Predictable interrupt latency
- No runtime drift
- No floating-point execution
- No configuration branching

---

## 4. Core Interrupt Flow Logic

The interrupt execution path is divided into three deterministic cases:

---

### Case 1 — Single Full Cycle  
- Condition: cycles == 1 && partial_cycle == 0

Behavior:

- Callback executed immediately
- Timer continues running unless STOP is explicitly called

This represents a single CTC interval delay.

---

### Case 2 — Single Cycle with Partial Extension  
- Condition: cycles == 1 && partial_cycle == 1

Behavior:

1. First interrupt:
   - Counter reset
   - Partial OCR value loaded
   - Static state updated

2. Second interrupt:
   - Counter reset
   - Full OCR restored
   - Static state cleared
   - Callback executed

This implements deterministic two-stage completion.

---

### Case 3 — Multiple Cycles with Partial Finalization  
- Condition: cycles > 1 && partial_cycle == 1


Behavior:

1. Full-cycle interrupts execute normally
2. When reaching final boundary:
   - Partial OCR scheduled
3. After partial completion:
   - OCR restored
   - Internal counters reset
   - Callback executed

State management is handled using static internal flags:

- `count`
- `partial_set_flag`
- `partial_finished`

These flags form a controlled interrupt transition system.

---

## 5. Manual Counter Reset Strategy

Inside ISR:

- `timer_reset_counter(h)` is called explicitly

Even though CTC auto-clears on compare match, manual reset ensures:

- Deterministic cycle boundary control
- Clean transition between full and partial OCR values
- Precise alignment before callback execution

This reflects hardware-level awareness.

---

## 6. OCR Switching Mechanism

Two OCR configurations are precomputed:

- Full-cycle OCR
- Partial-cycle OCR

The ISR switches between them using:

- `set_ocr_value(h)`
- `set_partial_ocr_value(h)`

No recalculation occurs during switching.

The ISR only applies precomputed register values.

This prevents runtime timing distortion.

---

## 7. Callback Execution Model

Callback is executed strictly at the completion boundary.

It is triggered only after:

- All full cycles are completed
- Partial cycle (if present) is completed
- State variables are restored to baseline

The callback runs inside ISR context.

The driver guarantees timing completion.
Lifecycle control remains external.

---

## 8. Explicit Lifecycle Control

Important:

The ISR does not stop the timer automatically.

Timer stopping is controlled exclusively by:

- `TIMER_STOP()`
- `TIMER_DEINIT()`

This separation ensures:

- Clear ownership boundaries
- No hidden hardware state changes
- Deterministic execution behavior

Interrupt flow handles progression.
API handles lifecycle.

---

## 9. Deterministic State Engine Characteristics

This interrupt flow demonstrates:

- State-driven execution
- Precomputed timing transitions
- Controlled OCR switching
- Explicit counter boundary resets
- Static state containment inside ISR
- No runtime math inside interrupt context

The ISR functions as a hardware-backed timing state controller.

---

## 10. System-Level Impact

This design ensures:

- Interrupt latency remains minimal
- Execution remains predictable
- No drift accumulation
- Scalable multi-cycle delay support
- Clean separation between configuration and execution
- Explicit lifecycle governance

The interrupt does not behave as a simple callback trigger.

It operates as a deterministic timing transition engine.

---

## 11. Engineering Characteristics

The interrupt flow reflects:

- Hardware-first design discipline
- Deterministic state-machine modeling
- Clean separation of responsibility
- API-governed lifecycle management
- Controlled register switching
- Precise cycle-boundary management

This is not a generic ISR implementation.

It is a structured interrupt-driven timing subsystem.

---

This completes the interrupt flow architecture for the non-blocking timer engine.