# BatteryState - Reverse Engineering Documentation

## Executive Summary
`BatteryState` is an abstract class that represents the state of a single battery on a device. it provides a high-level interface to query the presence of hardware, its charging status, and the remaining capacity. It serves as a data holder and abstraction layer over the underlying battery hardware details.

## Architecture Overview
`BatteryState` is part of the `android.hardware` package. It is designed as an abstract base class, likely implemented by concrete classes that interface with the `BatteryManager` or direct HAL implementations. It uses an integer-based enumeration for battery status, mapping to constants defined in `BatteryManager`.

## Detailed Functionality

### `isPresent()`
**Purpose**: Determines if the device actually has battery hardware.
**Algorithm**: Abstract method to be implemented by the platform-specific subclass.
**Java-Specific Notes**: Returns a `boolean`.
**C++ Implementation Guidance**: Should return `bool`.

### `getStatus()`
**Purpose**: Retrieves the current charging status of the battery.
**Algorithm**: Abstract method. Returns one of the `STATUS_*` constants.
**Java-Specific Notes**: Annotated with `@BatteryStatus` (`IntDef`) for compile-time safety.
**C++ Implementation Guidance**: Use an `enum class BatteryStatus` to represent the statuses.

### `getCapacity()`
**Purpose**: Retrieves the remaining battery capacity as a percentage.
**Algorithm**: Abstract method. Returns a float in the range [0.0, 1.0]. Returns `NaN` if unreadable.
**Java-Specific Notes**: Annotated with `@FloatRange(from = -1.0f, to = 1.0f)`.
**C++ Implementation Guidance**: Use `float`. Use `std::numeric_limits<float>::quiet_NaN()` for the error state.

## Data Model
- **BatteryStatus (int)**:
    - `STATUS_UNKNOWN` (0)
    - `STATUS_CHARGING` (1)
    - `STATUS_DISCHARGING` (2)
    - `STATUS_NOT_CHARGING` (3)
    - `STATUS_FULL` (4)

## API Reference
- `public abstract boolean isPresent()`
- `public abstract int getStatus()`
- `public abstract float getCapacity()`

## Java-to-C++ Translation Guide
- **Class**: `abstract class BatteryState` -> `class BatteryState` (abstract with virtual methods).
- **Constants**: Static final ints -> `enum class BatteryStatus : int32_t`.
- **Annotations**: `@BatteryStatus`, `@FloatRange` -> Documented constraints in C++ comments or enforced via strong types if applicable.

## Test Cases & Validation
- Verify `isPresent()` returns true on mobile devices and false on emulators/tethers if applicable.
- Verify `getStatus()` transitions correctly between charging and discharging when power is connected/disconnected.
- Verify `getCapacity()` returns values within 0.0 and 1.0.

## Implementation Risks
- Precision of float capacity across different HAL implementations.
- Mapping of proprietary battery statuses to standard Android statuses.
