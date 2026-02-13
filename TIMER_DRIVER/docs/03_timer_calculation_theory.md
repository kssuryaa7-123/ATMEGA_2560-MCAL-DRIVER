# 03. Timer Calculation Theory

## 1. System Clock Foundation

The driver operates using the default ATmega2560 system clock:

F_CPU = 16 MHz

This means:

1 clock cycle = 1 / 16,000,000 seconds  
1 clock cycle = 0.0625 µs

Since:

1 µs = 16 clock cycles

All timing calculations inside the driver are derived from this constant relationship.

---

## 2. Time Normalization

The user API allows delay input in:

- Seconds
- Milliseconds
- Microseconds

Example:

timer_delay(10, SEC);

Internally, all time values are normalized to microseconds using:

- `time_to_microsec()` function.

This ensures a unified mathematical pipeline.

All further calculations operate only in microseconds.

---

## 3. Timer Tick Formula

Core formula:

- T_tick = Prescaler / F_CPU

Since F_CPU = 16 MHz:

- Tick_time (µs) = Prescaler / 16

Tick duration per prescaler:

- Prescaler = 1     → 0.0625 µs  
- Prescaler = 8     → 0.5 µs  
- Prescaler = 64    → 4 µs  
- Prescaler = 256   → 16 µs  
- Prescaler = 1024  → 64 µs  

These values define timer resolution.

---

## 4. Maximum Delay Before Overflow

### 8-bit Timer (256 counts)

Max Delay = 256 × T_tick

- Prescaler 1     → 16 µs  
- Prescaler 8     → 128 µs  
- Prescaler 64    → 1024 µs  
- Prescaler 256   → 4096 µs  
- Prescaler 1024  → 16384 µs  

Therefore:

If delay < 16384 µs → 8-bit timer is sufficient.

---

### 16-bit Timer (65536 counts)

Max Delay = 65536 × T_tick

- Prescaler 1     → 4096 µs  
- Prescaler 8     → 32768 µs  
- Prescaler 64    → 262144 µs  
- Prescaler 256   → 1048576 µs  
- Prescaler 1024  → 4194304 µs  

This enables large delay generation.

---

## 5. Timer Selection Strategy

### Blocking Mode

If:

Delay < 16384 µs

→ TIMER0 (8-bit)

Else

→ TIMER1 (16-bit)

This boundary is mathematically derived from:

8-bit max delay at prescaler 1024.

---

### Non-Blocking Mode

Always uses:

→ TIMER3 (16-bit)

This isolates ISR-driven timing from blocking execution.

---

## 6. Prescaler Selection Logic

The prescaler is selected using threshold comparison against the mathematically derived maximum delay values.

Example (8-bit blocking):

- if delay ≤ 16 µs      → PRESCALER_1  
- if delay ≤ 128 µs     → PRESCALER_8  
- if delay ≤ 1024 µs    → PRESCALER_64  
- if delay ≤ 4096 µs    → PRESCALER_256  
else                  → PRESCALER_1024  

The smallest valid prescaler is always selected.

This ensures:

- Maximum timing resolution
- Minimum quantization error
- Efficient hardware utilization

---

## 7. Total Tick Calculation

Floating-point arithmetic is used for precision:

ticks = (delay_us × 16.0) / prescaler

This computes the exact required timer counts before integer conversion.

---


## 8. Tick Conversion Pipeline (Implementation Order)

The driver follows a strict deterministic sequence before loading the OCR register.

### Step 1
Delay is normalized to microseconds.

### Step 2
Timer type is selected (8-bit / 16-bit).

### Step 3
Prescaler is selected using threshold comparison.

### Step 4
Exact floating-point tick count is computed:

ticks_float = (delay_us × 16.0) / prescaler

This represents the theoretical number of timer increments required.

### Step 5
Mode-based tick conversion is applied to ensure correct timing guarantees:

- 8-bit Blocking → ceil(ticks_float)  
  (Guarantees actual delay ≥ requested delay. Required for strict lower-bound timing in short protocol-level delays.)

- 16-bit Blocking → round(ticks_float)  
  (Optimizes overall accuracy for larger delays where ±1 tick error is negligible.)

- Non-Blocking → round(ticks_float)  
  (Provides balanced precision for ISR-driven timing while maintaining stable cycle control.)

ticks = integer value


### Step 6
OCR is computed:

OCR = ticks − 1

(Subtraction is required because the timer counts from 0 to OCR inclusive.)

### Step 7
OCR and cycle information are stored inside the timer handle.

This pipeline guarantees mathematically consistent and deterministic configuration.

---


## 9. OCR Derivation in CTC Mode

In Clear Timer on Compare (CTC) mode, the timer counts from 0 to OCR inclusive.

Therefore:

OCR = ticks − 1

This ensures that the total number of timer increments equals the computed tick count.

Register width depends on the selected timer:

- TIMER0 → 8-bit OCR  
- TIMER1 / TIMER3 → 16-bit OCR  

---

## 10. Multi-Cycle Delay Handling

When the required tick count exceeds single-cycle capacity (65536 for 16-bit timer), the delay is decomposed into deterministic cycles.

cycles = ticks / 65536  
remaining = ticks % 65536  

Execution strategy:

- Full cycles operate with OCR = 65535  
- Final partial cycle operates with OCR = remaining − 1  

Cycle transitions are managed by either:

- Blocking polling loop (blocking mode), or  
- Compare Match ISR (non-blocking mode)

This architecture enables arbitrarily long delays while preserving mathematical accuracy.

---

## 11. Non-Blocking ISR Control Flow

In non-blocking mode:

- TIMER3 operates in CTC configuration  
- The ISR (TIMER3_COMPA_vect) decrements cycle counters  
- Partial cycle switching is handled dynamically  
- User callback executes only after final cycle completion  

This guarantees:

- Deterministic interrupt-driven delay execution  
- Precise long-duration timing  
- Clean separation from foreground execution  

---

## 12. Deterministic Mathematical Model

The driver is fully derived from hardware timer principles and three governing equations:

1) T_tick = Prescaler / F_CPU  
2) ticks = (delay_us × 16) / prescaler  
3) OCR = ticks − 1  

All configuration decisions — timer selection, prescaler choice, rounding policy, and cycle handling — are direct consequences of these relationships.

No empirical tuning or heuristic adjustments are used.

The design is fully analytical and hardware-constrained.
