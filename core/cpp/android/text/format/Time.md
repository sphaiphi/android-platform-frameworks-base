# Time - Reverse Engineering Documentation

## Executive Summary
**Deprecated** replacement for `struct tm`. Represents a moment in time with fields (year, month, day, hour, minute, second).

## Issues
- **Y2038**: Uses 32-bit math.
- **Thread-safety**: Not thread safe.

## API Reference
- **`set(long millis)`**: Sets fields from epoch time.
- **`toMillis(boolean ignoreDst)`**: Converts fields to epoch time.
- **`format`**: strftime-style formatting.
- **`normalize`**: Normalizes fields (e.g. "Oct 32" -> "Nov 1").

## Java-to-C++ Translation Guide
- **Legacy**: Do not use for new code. Use `std::chrono` or `icu::Calendar`.
- **Implementation**: Uses `TimeCalculator` (C++ port) to handle timezone calculations.
