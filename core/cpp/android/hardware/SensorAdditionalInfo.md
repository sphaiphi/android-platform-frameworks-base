# SensorAdditionalInfo - Reverse Engineering Documentation

## Executive Summary
`SensorAdditionalInfo` represents extra metadata frames reported by sensors through the `onSensorAdditionalInfo` callback. These frames provide calibration data, sensor placement info, internal temperature, and other non-standard measurements.

## Architecture Overview
This is a data holder class. It contains payload data in both float and integer arrays, along with a type and serial number to identify the frame's content.

## Detailed Functionality

### Frame Types
- `TYPE_FRAME_BEGIN` (0) / `TYPE_FRAME_END` (1): Delineate a set of info frames.
- `TYPE_UNTRACKED_DELAY` (0x10000): Jitter and processing delay.
- `TYPE_INTERNAL_TEMPERATURE` (0x10001).
- `TYPE_VEC3_CALIBRATION` (0x10002): Transformation matrix for 3-axis sensors.
- `TYPE_SENSOR_PLACEMENT` (0x10003): 3x4 matrix describing physical orientation and location relative to the device origin.
- `TYPE_SAMPLING` (0x10004): Raw sample period and jitter.

### Helper Methods
- `createLocalGeomagneticField(...)`: Internal factory for geomagnetic info.
- `createCustomInfo(...)`: Factory for vendor-defined info.

## Data Model
- `sensor`: The `Sensor` that generated the event.
- `type` (int): Identifier for the info type.
- `serial` (int): Sequence number.
- `floatValues` (float[]): Payload.
- `intValues` (int[]): Payload.

## Java-to-C++ Translation Guide
- **Class**: `class SensorAdditionalInfo` -> `struct SensorAdditionalInfo`.
- **Matrices**: `TYPE_SENSOR_PLACEMENT` uses a 3x4 row-major matrix. C++ should provide helpers to convert this to standard math library types (e.g., GLM or Eigen).

## Implementation Risks
- Interpretation of matrix data: Ensuring the Android coordinate system conventions are strictly followed.
- Vendor extensions: Manufacturers can define custom types, requiring flexible handling.
