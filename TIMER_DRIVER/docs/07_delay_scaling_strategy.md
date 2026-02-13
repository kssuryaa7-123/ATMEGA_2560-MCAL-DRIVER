# 07. Delay Scaling Strategy

## 1. Design Objective

Microcontroller timers are bounded by hardware constraints.

- 8-bit timers: maximum count = 255
- 16-bit timers: maximum count = 65535

Any delay request exceeding these limits cannot be generated in a single hardware cycle.

The Delay Scaling Strategy defines how large delays are decomposed, structured, and executed deterministically without violating hardware boundaries.

This transforms a limited hardware timer into a scalable timing engine.

---

## 2. Hardware Constraint Awareness

Given:

F_CPU = 16 MHz

Tick calculation:

ticks = (delay_us × 16.0) / prescaler

If:

ticks > MAX_TIMER_COUNT

A direct OCR assignment is impossible.

Therefore, delay must be decomposed into multiple controlled cycles.

This is not a workaround.

It is a structured scaling mechanism.

---

## 3. Analytical Decomposition Model

Let:

MAX_COUNT = 65536 (for 16-bit TIMER3)

If:

required_ticks > MAX_COUNT

Then:

full_cycles = required_ticks / MAX_COUNT  
remaining_ticks = required_ticks % MAX_COUNT  

This produces:

- N full hardware cycles
- One optional partial cycle

Where:

- Full cycle → OCR = MAX_COUNT - 1
- Partial cycle → OCR = remaining_ticks - 1

All values are computed before execution begins.

No runtime calculation occurs inside ISR.

---

## 4. Deterministic Multi-Cycle Execution

The driver executes delay in controlled phases:

1. Full cycles execute sequentially
2. Final partial cycle executes (if required)
3. Completion boundary triggers callback

The scaling is:

- Deterministic
- Finite
- Precomputed
- State-controlled

The hardware never exceeds its register capacity.

The driver extends time logically, not electrically.

---

## 5. Blocking Mode Scaling

In blocking mode:

- Each full cycle is polled synchronously
- Compare flag is checked
- Counter is reset deterministically
- Final partial cycle completes the delay

CPU remains intentionally occupied.

Scaling preserves deterministic busy-wait behavior.

---

## 6. Non-Blocking Mode Scaling

In non-blocking mode:

- Full cycles are managed via interrupt transitions
- Partial cycle is scheduled at final boundary
- Callback is triggered only after all cycles complete

The ISR transitions between full and partial OCR values.

Lifecycle control remains external (START / STOP / DEINIT).

Scaling remains entirely precomputed.

---

## 7. Precision and Error Containment

Scaling preserves timing accuracy by:

- Using analytical tick computation
- Applying rounding for symmetry
- Avoiding cumulative error
- Preventing drift across cycles

Each cycle represents an exact hardware-defined interval.

No additive timing distortion occurs during decomposition.

---

## 8. Resource Preservation

Scaling does not:

- Modify clock frequency
- Alter hardware configuration mid-execution
- Depend on software delay loops
- Require nested timers

It respects:

- Native timer boundaries
- Register capacity
- Interrupt predictability

This reflects resource-aware firmware engineering.

---

## 9. Why This Strategy Matters

Without scaling:

- Large delays would overflow
- Timing would become undefined
- Precision would degrade
- Hardware would behave unpredictably

With scaling:

- Delays become arbitrarily extendable
- Execution remains deterministic
- Architecture remains clean
- Hardware integrity is preserved

The timer becomes scalable through mathematical extension.

---

## 10. Engineering Characteristics

The Delay Scaling Strategy demonstrates:

- Hardware limitation awareness
- Analytical decomposition modeling
- Deterministic multi-cycle structuring
- Separation between computation and execution
- Cross-mode scalability (blocking & non-blocking)
- Controlled partial-cycle scheduling

This is not simple overflow handling.

It is structured time extension through deterministic state modeling.

---

This completes the delay scaling architecture of the timer driver.
