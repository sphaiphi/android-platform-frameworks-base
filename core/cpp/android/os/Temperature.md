# Temperature - Reverse Engineering Documentation

## Executive Summary
`Temperature` is a data class used by the `ThermalService` to represent the current thermal state of various hardware components (CPU, GPU, Battery, etc.). It encapsulates the measured temperature value, the component type, and the current throttling severity level.

## Architecture Overview
- **Data Container**: Immutable and Parcelable.
- **Source**: Values are typically provided by the Thermal HAL and propagated through `IThermalService`.
- **Usage**: Used to notify applications and system services about overheating components so they can adjust their power consumption.

## Detailed Functionality

### Component Categorization
**Purpose**: To identify which part of the device is heating up.
**Types**:
- `TYPE_CPU`, `TYPE_GPU`, `TYPE_BATTERY`.
- `TYPE_SKIN`: External surface temperature (critical for user comfort).
- `TYPE_USB_PORT`: Monitors for heat during high-speed charging.
- `TYPE_NPU`, `TYPE_TPU`, `TYPE_MODEM`.

### Throttling Severity
**Purpose**: To indicate the urgency of power reduction.
**Levels**:
- `THROTTLING_NONE`: Normal operation.
- `THROTTLING_LIGHT` to `THROTTLING_SEVERE`: Increasing levels of performance reduction.
- `THROTTLING_CRITICAL`: Maximum throttling; system may start closing apps.
- `THROTTLING_EMERGENCY`: Immediate shutdown of hardware blocks.
- `THROTTLING_SHUTDOWN`: Full device shutdown to prevent damage.

## Data Model

### Members
- `mValue` (`float`): Temperature in degrees Celsius.
- `mType` (`int`): Component type constant.
- `mName` (`String`): Sensor identifier (e.g., "cpu-thermal").
- `mStatus` (`int`): Throttling status constant.

## API Reference

### Public Methods
- `float getValue()`
- `int getType()`
- `String getName()`
- `int getStatus()`

## Java-to-C++ Translation Guide

### Enum Mapping
- **Java**: Uses `@IntDef` constants.
- **C++**: Use `enum class TemperatureType` and `enum class ThrottlingSeverity` to match the AIDL definitions in `android.hardware.thermal`.

### Struct Definition
- **Java**: Parcelable class.
- **C++**: A simple `struct` or `class` with `readFromParcel` and `writeToParcel` methods.

## Test Cases & Validation
1. **Valid Ranges**: Ensure that `getValue()` returns reasonable numbers (typically -20 to 150) and that `getStatus()` maps to a valid level.
2. **Type Identity**: Verify that `TYPE_BATTERY` corresponds to the same hardware sensor reported by `BatteryManager`.
3. **Parcel Round-trip**: Ensure the `name` and `value` are preserved across IPC.

## Implementation Risks
- **Sensor Naming**: Sensor names vary by vendor and kernel version. The C++ implementation must handle arbitrary strings for `mName`.
- **Accuracy**: Temperature sensors can be noisy. The framework often applies low-pass filters before reporting values to apps.
- **HAL Compatibility**: Newer devices may report types (like `TYPE_POGO`) that older system services might not recognize.
