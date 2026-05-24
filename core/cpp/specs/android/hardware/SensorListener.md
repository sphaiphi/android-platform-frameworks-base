# SensorListener - Reverse Engineering Documentation

## Executive Summary
`SensorListener` is a legacy interface used for receiving sensor change notifications. It has been replaced by `SensorEventListener` and is now deprecated. It remains in the codebase primarily for backward compatibility.

## Architecture Overview
This interface uses integer-based sensor IDs instead of `Sensor` objects. It is used in conjunction with older `SensorManager` methods.

## Detailed Functionality

### `onSensorChanged(int sensor, float[] values)`
**Purpose**: Delivered when sensor values change.
**Coordinate System**: In this legacy API, axes are swapped when the device's screen orientation changes (e.g., rotating from portrait to landscape).
**Indices**:
- `values[0..2]`: Transformed values.
- `values[3..5]`: Raw (unswapped) values.

### `onAccuracyChanged(int sensor, int accuracy)`
**Purpose**: Delivered when the accuracy of a sensor changes.

## Data Model
- **Sensor IDs**: `SENSOR_ORIENTATION`, `SENSOR_ACCELEROMETER`, etc. (integer bitmasks).

## Java-to-C++ Translation Guide
- **Deprecated Status**: If possible, do not implement this in modern C++ code unless legacy binary compatibility is a strict requirement.
- **Mapping**: If required, use `LegacySensorManager` logic to map native events back to these legacy indices and coordinate systems.

## Implementation Risks
- Swapped coordinate system logic is error-prone and differs from all other Android APIs.
- Mixing legacy and modern listeners can lead to inconsistent behavior if not handled by a central manager.
