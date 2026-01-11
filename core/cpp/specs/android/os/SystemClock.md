# SystemClock - Reverse Engineering Documentation

## Executive Summary
`SystemClock` provides access to various system timers and clocks. It distinguishes between "wall clock" time (which can change) and "monotonic" time (which cannot).

## Architecture Overview
-   **Role**: Time source.
-   **Native**: Most methods are `@CriticalNative` calls into JNI (mapping to `clock_gettime` variants).

## Data Model
-   **`uptimeMillis()`**: `CLOCK_MONOTONIC`. Time since boot, *pauses in deep sleep*. Basis for `Handler` timing.
-   **`elapsedRealtime()`**: `CLOCK_BOOTTIME`. Time since boot, *includes deep sleep*. Best for general interval timing.
-   **`currentThreadTimeMillis()`**: `CLOCK_THREAD_CPUTIME_ID`. CPU time consumed by current thread.

## API Reference
-   `sleep(long ms)`: Convenience for `Thread.sleep` that ignores InterruptedExceptions (but restores interrupt status).
-   `setCurrentTimeMillis(long)`: Sets wall clock (requires permission).

## Java-to-C++ Translation Guide
-   **Equivalents**:
    -   `uptimeMillis` -> `android::os::uptimeMillis()` (utils/SystemClock.h).
    -   `elapsedRealtime` -> `android::elapsedRealtime()`.
-   **Standard C++**: `std::chrono::steady_clock` (usually monotonic), `std::chrono::system_clock` (wall). Android specific clocks (`CLOCK_BOOTTIME`) might require custom wrappers or `clock_gettime` directly.
