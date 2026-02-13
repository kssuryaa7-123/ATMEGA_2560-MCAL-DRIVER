# 04. Blocking Mode Design

## 1. Design Objective

Blocking mode provides fully synchronous, deterministic delay execution.

When invoked, program execution is intentionally halted until the requested delay duration has completely elapsed.

This mode is designed for:

- Deterministic hardware stabilization
- Protocol timing enforcement
- Peripheral initialization sequences
- Short critical timing windows

The objective is precision and predictability over concurrency.

---

## 2. Architectural Philosophy

Blocking mode is designed under three core principles:

1. Hardware-first derivation  
2. Minimal resource footprint  
3. Deterministic execution guarantee  

All configuration decisions are mathematically derived from timer capacity and system clock constraints.

No empirical tuning or arbitrary constants are used.

The smallest capable timer is always selected to preserve higher-resolution hardware for other subsystems.

---

## 3. Timer Allocation Strategy

Timer selection is based strictly on calculated delay capacity.

- Delay < 16384 µs → TIMER0 (8-bit)
- Delay ≥ 16384 µs → TIMER1 (16-bit)

The boundary corresponds to the maximum achievable delay of the 8-bit timer at prescaler 1024.

This ensures:

- Optimal hardware utilization  
- Maximum achievable resolution  
- Scalable delay handling  

---

## 4. Operating Mode Configuration

Blocking mode operates using CTC (Clear Timer on Compare) mode.

Configuration sequence:

1. Select appropriate timer  
2. Configure CTC mode  
3. Load computed OCR value  
4. Configure prescaler  
5. Reset counter register (TCNT)  
6. Start timer  

On compare match, the counter automatically resets to zero.

This guarantees cycle-level precision without manual overflow handling.

---

## 5. Execution Control Flow

Blocking delay follows a deterministic runtime sequence:

1. Delay API invoked  
2. Time normalized to microseconds  
3. Timer selected  
4. Prescaler selected  
5. OCR value computed  
6. Timer started  
7. CPU enters polling loop  
8. Compare Match flag monitored  
9. Flag cleared on match  
10. Multi-cycle accounting handled  
11. Timer stopped after final cycle  

Execution returns only after full delay completion.

The CPU remains exclusively dedicated to timing during this period.

---

## 6. Polling-Based Determinism

Blocking mode intentionally avoids interrupts.

Instead, it continuously monitors:

- OCF0 (TIMER0)
- OCF1A (TIMER1)

This eliminates:

- ISR latency
- Context switching overhead
- Interrupt scheduling uncertainty

Result:

Fully predictable delay execution at the hardware cycle level.

---

## 7. Large Delay Handling (Multi-Cycle Decomposition)

Blocking mode is not limited to single-cycle timer capacity.

For delays exceeding:

- 256 counts (8-bit)
- 65536 counts (16-bit)

The delay is decomposed into deterministic full cycles and a final partial cycle.

Execution model:

- Full cycles execute sequentially
- Each cycle waits for compare match
- Remaining partial cycle executes last

This allows generation of arbitrarily long delays using TIMER1.

Delay duration is therefore not constrained by single 16-bit overflow limits.

This demonstrates architectural scalability beyond basic timer usage.

---

## 8. Deterministic Timing Guarantee

Blocking mode guarantees:

- Exact cycle accounting
- Controlled rounding strategy
- No interrupt interference
- No timing drift accumulation

In 8-bit blocking mode:

ceil() rounding ensures:

Actual delay ≥ Requested delay

This protects protocol-sensitive timing from underflow risk.

All behavior is analytically derived from timer equations.

---

## 9. Hardware Resource Finalization

After delay completion:

- Timer is stopped
- Prescaler bits are cleared
- Compare flags are cleared
- Counter is left in a defined state

This guarantees:

- Clean hardware state
- No unintended background counting
- Safe reuse by other modules

---

## 10. Design Trade-Off Analysis

Blocking mode intentionally prioritizes:

Determinism over concurrency.

Advantages:

- Cycle-level predictable timing
- Zero interrupt overhead
- Simple and analyzable control flow
- Ideal for critical short delays

Limitations:

- CPU remains unavailable during delay
- Not suitable for multitasking systems

Blocking mode is therefore best suited for:

- Startup sequences
- Peripheral initialization
- Protocol-critical timing enforcement
- Low-complexity embedded systems

It provides maximum timing confidence with minimal architectural complexity.
