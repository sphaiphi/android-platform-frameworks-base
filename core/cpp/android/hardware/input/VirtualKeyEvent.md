# VirtualKeyEvent - Reverse Engineering Documentation

## Executive Summary
`VirtualKeyEvent` represents a key press or release event for virtual keyboards and D-pads.

## Architecture Overview
- **Parcelable**.
- **Immutable**.
- **Builder Pattern**.

## Detailed Functionality
- **Data**:
  - `mAction`: DOWN or UP.
  - `mKeyCode`: Android KeyCode.
  - `mEventTimeNanos`: Timestamp (optional, defaults to system time at injection).
- **Validation**: Checks for valid actions.

## Java-to-C++ Translation Guide
- Struct with `int32_t` action/keycode and `int64_t` time.

## Implementation Risks
- Time base consistency (`SystemClock.uptimeMillis()` vs Nanos).
