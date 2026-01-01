# Timestamp64.java - Reverse Engineering Documentation

## Executive Summary
`Timestamp64` represents the 64-bit timestamp format used by NTP/SNTP (RFC 5905). It consists of a 32-bit unsigned number of seconds since the start of an NTP era (default era 0 is Jan 1, 1900) and a 32-bit unsigned fractional second.

## Architecture Overview
- **Type**: Value Object (Immutable)
- **Package**: `android.net.sntp`.

## Detailed Functionality

### Core Logic
1.  **NTP Eras**: Since the 32-bit seconds field overflows every ~136 years, NTP uses "eras". Era 0 started in 1900. Era 1 will start in 2036. This class handles the math but requires the era number to be provided for absolute `Instant` conversion.
2.  **Fixed-Point Math**:
    -   The 32-bit fraction represents $1/2^{32}$ second units.
    -   `nanosToFractionBits`: $bits = (nanos \times 2^{32}) / 10^9$.
    -   `fractionBitsToNanos`: $nanos = (bits \times 10^9) / 2^{32}$.
3.  **Randomization**: `randomizeSubMillis` is used to implement the SNTP security recommendation of randomizing the lowest bits of the transmit timestamp to prevent simple spoofing.

### Constants
-   `OFFSET_1900_TO_1970`: 2,208,988,800 seconds.

## Data Model
-   `mEraSeconds`: `long` (treated as unsigned 32-bit).
-   `mFractionBits`: `int` (treated as unsigned 32-bit).

## API Reference
-   `fromInstant(Instant)`: Lossy conversion from Java time.
-   `toInstant(int era)`: Converts to absolute time given an era.
-   `randomizeSubMillis(Random)`: Randomizes bits below millisecond precision.

## Java-to-C++ Translation Guide

### Implementation
```cpp
class Timestamp64 {
public:
    static Timestamp64 from_instant(const std::chrono::system_clock::time_point& tp) {
        // Implementation of 1900-1970 offset math
    }

    uint64_t to_bits() const {
        return (m_era_seconds << 32) | (static_cast<uint32_t>(m_fraction_bits));
    }

    static uint32_t nanos_to_fraction(uint32_t nanos) {
        return static_cast<uint32_t>((static_cast<uint64_t>(nanos) << 32) / 1000000000ULL);
    }

private:
    uint32_t m_era_seconds;
    uint32_t m_fraction_bits;
};
```

### Critical Details
-   **Unsigned Math**: Java lacks unsigned 32-bit integers (until recently/via `Integer.toUnsignedLong`). C++ should use `uint32_t` explicitly.
-   **Precision**: Ensure the division/multiplication in `nanos_to_fraction` uses 64-bit intermediates to prevent overflow before division.
