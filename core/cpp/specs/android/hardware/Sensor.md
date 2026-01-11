# Sensor - Reverse Engineering Documentation

## Executive Summary
The `Sensor` class represents a specific hardware or software-defined sensor on the device. It provides detailed metadata about the sensor, such as its type, range, resolution, power consumption, and reporting mode.

## Architecture Overview
This is a data-heavy class that serves as a descriptor. It is populated via native bindings from the `SensorManager`. It includes constants for all standard Android sensor types and flags for reporting modes.

## Detailed Functionality

### Sensor Types
Extensive list of constants (e.g., `TYPE_ACCELEROMETER`, `TYPE_GYROSCOPE`, `TYPE_HEART_RATE`, `TYPE_HINGE_ANGLE`).

### Reporting Modes
- `REPORTING_MODE_CONTINUOUS` (0): Constant rate.
- `REPORTING_MODE_ON_CHANGE` (1): Reports on value change.
- `REPORTING_MODE_ONE_SHOT` (2): Deactivates after one event.
- `REPORTING_MODE_SPECIAL_TRIGGER` (3): Custom behavior (e.g., step detector).

### Wake-up Behavior
- `isWakeUpSensor()`: Indicates if the sensor can wake the Application Processor (AP) from suspend to deliver events.

### Direct Channel Support
- `isDirectChannelTypeSupported(sharedMemType)`: Checks if the sensor can stream data directly to a `MemoryFile` or `HardwareBuffer`.

## Data Model
- **Internal Fields**: `mName`, `mVendor`, `mVersion`, `mHandle`, `mType`, `mMaxRange`, `mResolution`, `mPower`, `mMinDelay`, `mFifoReservedEventCount`, `mFifoMaxEventCount`, `mStringType`, `mRequiredPermission`, `mMaxDelay`, `mFlags`, `mId`, `mUuid`.

## API Reference (Partial)
- `public String getName()`
- `public String getVendor()`
- `public int getType()`
- `public float getMaximumRange()`
- `public int getReportingMode()`
- `public boolean isWakeUpSensor()`
- `public boolean isDynamicSensor()`

## Java-to-C++ Translation Guide
- **Class**: `class Sensor` -> `class Sensor`.
- **Fields**: Map directly to a C++ POD struct for efficient passing from HAL.
- **Strings**: Use `android::String8`.
- **UUID**: Use `uint8_t[16]` or a dedicated UUID struct.

## Implementation Risks
- Maintaining parity between `sSensorReportingModes` array and the actual sensor type definitions.
- Handling vendor-defined sensors (`TYPE_DEVICE_PRIVATE_BASE`).
