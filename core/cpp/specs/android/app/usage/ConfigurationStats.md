# ConfigurationStats - Reverse Engineering Documentation

## Executive Summary
`ConfigurationStats` records usage statistics for a specific device configuration (e.g., a specific locale, orientation, or screen layout). It tracks how long the device was in that configuration and how many times it was activated.

## Architecture Overview
- **Implements**: `Parcelable`.
- **Dependency**: `android.content.res.Configuration`.

## Detailed Functionality

### Stats Tracking
- **Time Range**: `mBeginTimeStamp` to `mEndTimeStamp`.
- **Active Time**: `mTotalTimeActive` (duration) and `mLastTimeActive` (timestamp).
- **Count**: `mActivationCount` (number of times entered).
- **Configuration**: The `Configuration` object itself.

### Parceling Logic
- **Write**:
    - Configuration (if not null, write 1 then parcel; else write 0).
    - 4 `long`s (timestamps/durations).
    - 1 `int` (activation count).
- **Read**: Matches write order.

## Data Model

| Field | Type | Note |
| :--- | :--- | :--- |
| `mConfiguration` | Configuration | Nullable. |
| `mBeginTimeStamp` | long | Start of stats interval. |
| `mEndTimeStamp` | long | End of stats interval. |
| `mLastTimeActive` | long | Last timestamp usage occurred. |
| `mTotalTimeActive` | long | Total duration. |
| `mActivationCount` | int | Count. |

## API Reference
- Getters for all fields.
- Copy constructor.

## Java-to-C++ Translation Guide
- **Configuration**: Requires a C++ equivalent of `android.content.res.Configuration` and its Parcelable logic.
- **Timestamps**: `int64_t`.
- **Null Handling**: Check `mConfiguration` nullability during serialization.

## Implementation Risks
- **Configuration Parity**: The `Configuration` object is complex. Ensuring the C++ version matches the Java serialization exactly is critical.
