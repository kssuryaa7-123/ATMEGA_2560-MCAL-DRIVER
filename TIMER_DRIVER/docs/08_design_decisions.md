# 08. Architectural Design Decisions

## 1. Purpose of This Section

This document explains the intentional architectural decisions taken during the design of the timer driver.

The focus is not on how the system works, but why specific implementation paths were chosen over alternatives.

These decisions reflect hardware awareness, execution determinism, and lifecycle clarity.

---

## 2. CTC Mode Instead of Normal Mode

Decision:
Use CTC (Clear Timer on Compare Match) mode instead of Normal (overflow) mode.

Rationale:

- CTC provides deterministic boundary control.
- Compare match occurs at a programmable OCR value.
- No dependency on fixed overflow limits.
- Better accuracy for arbitrary delay generation.
- Cleaner scaling for multi-cycle decomposition.

Normal mode would require overflow tracking and introduce unnecessary accumulation logic.

CTC enables precise, programmable timing intervals.

This aligns with accuracy-driven design.

---

## 3. Timer Resource Allocation Strategy

Decision:

- Blocking Mode → TIMER0 (8-bit) and TIMER1 (16-bit)
- Non-Blocking Mode → TIMER3 (16-bit dedicated)

Rationale:

- Blocking execution is synchronous and self-contained.
- Non-blocking execution requires a dedicated interrupt vector.
- Separation prevents resource contention.
- Improves modular clarity.
- Avoids ISR conflicts across execution models.

Each execution model owns its timer resource.

This enforces hardware-level isolation.

---

## 4. Blocking Mode Lifecycle Behavior

Decision:

In blocking mode:
- Configuration and execution occur within the API call.
- Timer is stopped internally after completion.

Rationale:

- Blocking delay is synchronous.
- User expects API call to complete only after delay.
- Timer must not remain active after return.
- Internal stop ensures deterministic cleanup.

The blocking API owns its lifecycle fully.

No background behavior remains after function exit.

---

## 5. Non-Blocking Mode Lifecycle Separation

Decision:

Non-blocking mode separates:

- INIT
- START
- STOP
- DEINIT

Rationale:

- Interrupt-driven execution must not auto-stop.
- User retains execution control.
- Timer may be restarted without reinitialization.
- Lifecycle flexibility enables reuse.

The ISR does not stop the timer automatically.

Explicit control improves predictability.

This enforces clear ownership boundaries.

---

## 6. Manual STOP Instead of Automatic ISR Stop

Decision:

Do not stop timer automatically inside ISR after callback.

Rationale:

- Avoid hidden hardware state changes.
- Preserve deterministic execution model.
- Give user full lifecycle authority.
- Prevent implicit driver behavior.

Automatic stopping inside ISR would reduce transparency.

Explicit STOP() ensures controlled hardware behavior.

---

## 7. Precomputation Before Execution

Decision:

All tick calculations, cycle decomposition, and OCR values are computed before START.

Rationale:

- No runtime math inside ISR.
- Reduced interrupt latency.
- Prevent floating-point operations during execution.
- Eliminate timing drift caused by recalculation.

Execution phase is purely state-driven.

Configuration phase handles computation.

This separation improves determinism.

---

## 8. Strict Reconfiguration Model

Decision:

If user wants to change:

- Delay value
- Callback function
- Timing behavior

Then:

DEINIT → INIT must be performed.

Rationale:

- Prevent runtime mutation of active configuration.
- Avoid partial-state corruption.
- Preserve driver consistency.
- Enforce clear reconfiguration boundary.

This enforces architectural discipline.

---

## 9. Restart Without Reinitialization

Decision:

Allow START and STOP without reinitialization.

Rationale:

- Avoid redundant hardware configuration.
- Improve efficiency.
- Enable reusable periodic execution.
- Maintain lightweight lifecycle transitions.

Initialization configures hardware.

Start/Stop controls execution only.

---

## 10. Separation of Execution Models

Decision:

Blocking and Non-blocking are implemented independently.

Rationale:

- Different execution philosophies.
- Different lifecycle expectations.
- Different hardware usage models.
- Avoid mixed complexity.

Blocking = synchronous wait model.  
Non-blocking = interrupt-driven state engine.

This separation improves clarity and maintainability.

---

## 11. Engineering Characteristics of These Decisions

These architectural decisions demonstrate:

- Hardware-aware design
- Deterministic execution modeling
- Explicit lifecycle governance
- Resource isolation
- Configuration/execution separation
- Controlled state transitions

The driver is structured as a timing framework, not as a simple delay utility.

---

This concludes the architectural rationale behind the timer driver implementation.
