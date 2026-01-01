# LocationTime.java - Reverse Engineering Documentation

## Executive Summary
`LocationTime` is a simple immutable data class used to pass GNSS-derived time information. It pairs a Unix epoch timestamp with a corresponding system elapsed realtime timestamp, allowing synchronization between GNSS time and the system clock.

## Architecture Overview
- **Type**: Data Object / `Parcelable`
- **Package**: `android.location`
- **Implements**: `android.os.Parcelable`
- **Usage**: Used to convey the specific time associated with a location fix, correlating it to the monotonic system clock.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mUnixEpochTimeMillis` | `long` | Time in milliseconds since Jan 1, 1970 UTC. |
| `mElapsedRealtimeNanos` | `long` | Nanoseconds since system boot (monotonic). |

## API Reference

### Constructor
-   `LocationTime(long unixEpochTimeMillis, long elapsedRealtimeNanos)`: Initializes fields.

### Accessors
-   `getUnixEpochTimeMillis()`: Returns the Unix epoch time.
-   `getElapsedRealtimeNanos()`: Returns the elapsed realtime.

### Parcelable
-   Standard implementation. Writes Unix time first, then Elapsed realtime.

## Java-to-C++ Translation Guide

### Class Definition
A simple struct in C++.

```cpp
struct LocationTime {
    int64_t unix_epoch_time_millis;
    int64_t elapsed_realtime_nanos;
};
```

### Serialization
-   Read/Write two `int64` values in order.

## Usage Notes
This class is often used to check the age of a location fix or to synchronize sensor events with GNSS time. The key relationship is that `mUnixEpochTimeMillis` is the estimated real-world time when the system clock was at `mElapsedRealtimeNanos`.
