# Performance & Concurrency Reference

## Profile first, always

Optimization should be empirical, not guessed. Before changing anything for performance:

1. Profile to find the actual hot path (CPU profiling for hotspots, memory profiling for allocation patterns, cache profiling for miss rates).
2. Distinguish latency-sensitive from throughput-sensitive code — the right fix differs.
3. Benchmark with Google Benchmark (or equivalent) so the "before" number is real, not assumed.
4. After changing anything, verify byte-for-byte identical output before and after — a performance fix that silently changes behavior isn't a fix.

Algorithmic fixes (e.g., switching to Kahn's algorithm for topological sort, moving from recursive to iterative cycle detection, batching fuzzy-match calls instead of doing them one at a time) tend to produce far larger real-world speedups than micro-optimizations. Look for the algorithmic win before reaching for SIMD or manual unrolling.

## Optimization techniques, roughly in order of leverage

1. Algorithm complexity reduction (the biggest lever, usually)
2. Data structure selection matched to actual access patterns
3. Memory layout optimization and cache-friendly design
4. Branch prediction hints, SIMD vectorization, loop unrolling/fusion (smallest lever, last resort)

## Concurrency threading primitives

- `std::thread`/`std::jthread` (prefer `jthread` for automatic join and cooperative cancellation).
- RAII-based mutexes and locks — never a manual lock/unlock pair.
- Condition variables for wait/notify coordination.
- Atomics and memory ordering — understand the ordering guarantee actually needed (relaxed/acquire-release/seq_cst) rather than defaulting to the strongest one out of caution everywhere.
- Thread-local storage where per-thread state is genuinely the right model.

## Lock-free programming

Only reach for this when profiling has shown lock contention is the actual bottleneck — lock-free code trades simplicity for throughput and the trade is not always worth it.

- Compare-and-swap patterns as the basic building block.
- Memory barriers and the ABA problem — know the standard mitigations (tagged pointers, hazard pointers, epoch-based reclamation).
- Wait-free algorithms are a further step up in complexity from lock-free; reserve them for cases with a proven need.

## Async programming

- Coroutines and task types for structured async control flow.
- Future/promise patterns for simpler one-shot async results.
- Executors and schedulers to control where async work actually runs.
- Cancellation tokens designed in from the start, not bolted on later.
- Async I/O patterns (e.g., via ASIO) for network- or file-bound work.

## Concurrent design patterns

- Active object, monitor object, thread pool, producer-consumer, and read-write lock patterns cover most concurrent design needs — recognize which shape a problem matches before inventing something bespoke.

## Low-level memory optimization

- Small object optimization, pool allocators, and arena allocators for allocation-heavy hot paths.
- Memory alignment and cache-line awareness (false sharing is a common, easy-to-miss concurrency performance bug).

## Code generation

- Inline assembly and compiler intrinsics only when the compiler demonstrably can't generate the needed code otherwise.
- Link-time optimization and profile-guided optimization as project-level levers, not per-function ones.
