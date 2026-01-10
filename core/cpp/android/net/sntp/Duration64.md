# Duration64.java - Reverse Engineering Documentation

## Executive Summary
`Duration64` is a signed 64-bit value representing the difference between two NTP 64-bit timestamps. It is used in SNTP calculations (like clock offset and round-trip delay) where the magnitude is within +/- 34 years.

## Architecture Overview
- **Type**: Value Object (Immutable)
- **Package**: `android.net.sntp`
- **Relationship**: Derived from `Timestamp64`.

## Detailed Functionality
-   **Calculation**: Computed as `endTimestamp.bits - startTimestamp.bits`. 
-   **Precision**: Uses a fixed-point representation where the upper 32 bits are signed seconds and the lower 32 bits are fractional seconds.
-   **Conversion**:
    -   `toDuration()`: Converts to `java.time.Duration` (nanosecond precision). This conversion is potentially lossy because NTP's 32-bit fraction has higher precision (~232 picoseconds) than nanoseconds.
    -   `fromDuration(Duration)`: Creates a `Duration64` from a standard Java Duration.

## Data Model
-   `mBits`: `long`. 
    -   Bits 63-32: Signed seconds.
    -   Bits 31-0: Unsigned fractional bits.

## Java-to-C++ Translation Guide

### Implementation
```cpp
class Duration64 {
public:
    static Duration64 between(const Timestamp64& start, const Timestamp64& end) {
        return Duration64(end.to_bits() - start.bits());
    }

    int32_t get_seconds() const { return static_cast<int32_t>(bits_ >> 32); }
    uint32_t get_nanos() const {
        return Timestamp64::fraction_bits_to_nanos(static_cast<uint32_t>(bits_ & 0xFFFFFFFFL));
    }

private:
    explicit Duration64(int64_t bits) : bits_(bits) {}
    int64_t bits_;
};
```

### Safety
Ensure the subtraction handles 64-bit signed overflow correctly according to the modular arithmetic defined in the NTP spec (RFC 5905).
