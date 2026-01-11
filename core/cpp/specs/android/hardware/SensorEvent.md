# SensorEvent - Reverse Engineering Documentation

## Executive Summary
`SensorEvent` is a data container used to deliver sensor readings to applications. It holds the sensor's values, timestamp, accuracy, and type. It also defines the standard Android sensor coordinate system.

## Architecture Overview
This class is frequently instantiated and reused. In the system framework, these objects are often pooled to reduce GC pressure. It is primarily used as a parameter in `SensorEventListener.onSensorChanged`.

## Detailed Functionality

### Coordinate System
- **X axis**: Horizontal, points to the right.
- **Y axis**: Vertical, points up.
- **Z axis**: Points out of the front face of the screen.
- **Note**: This system does NOT change when the screen rotates.

### Values Interpretation
Contents of the `values` array depend on sensor type:
- **Accelerometer**: SI units (m/s^2). Includes gravity unless high-pass filtered.
- **Magnetic Field**: micro-Tesla (uT).
- **Gyroscope**: radians/second. Positive is counter-clockwise (right-hand rule).
- **Light**: SI lux.
- **Pressure**: hPa (millibar).
- **Proximity**: centimeters.
- **Rotation Vector**: Unit quaternion components.

### Discontinuity
- `firstEventAfterDiscontinuity`: Boolean indicating a major change in the reference frame (relevant for head trackers).

## Data Model
- `values` (float[]): The actual data.
- `sensor` (Sensor): Source.
- `accuracy` (int): Reliability (e.g., `SENSOR_STATUS_ACCURACY_HIGH`).
- `timestamp` (long): Nanoseconds (base: `SystemClock.elapsedRealtimeNanos()`).

## Java-to-C++ Translation Guide
- **Class**: `class SensorEvent` -> `struct SensorEvent`.
- **Memory**: In C++, this should be a stack-allocated or pooled struct to match the high-frequency event delivery.
- **Timestamp**: Use `int64_t`.

## Implementation Risks
- Floating point precision.
- Timestamp alignment across different sensors.
- Ensuring `values` array is large enough for the specific sensor type (can be up to 16 for `TYPE_POSE_6DOF`).
