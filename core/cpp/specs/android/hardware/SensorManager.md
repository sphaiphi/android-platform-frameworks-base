# SensorManager - Reverse Engineering Documentation

## Executive Summary
`SensorManager` is the abstract base class that provides access to the device's sensors. It allows applications to list available sensors, register listeners for sensor data, control reporting rates, and manage high-performance direct data channels.

## Architecture Overview
`SensorManager` follows the Service Manager pattern. It acts as an entry point for the Sensor Subsystem. Concrete implementations (like `SystemSensorManager`) handle the actual IPC with the `sensorservice` system process.

## Detailed Functionality

### Sensor Discovery
- `getSensorList(type)`: Returns a list of sensors of a specific type (e.g., `TYPE_ACCELEROMETER`).
- `getDefaultSensor(type)`: Returns the default sensor for a type, optionally filtered by wake-up capability.

### Listener Registration
- `registerListener(...)`: Enables a sensor and starts delivering events to a `SensorEventListener`. Supports sampling periods and batching latency.
- `unregisterListener(...)`: Disables the sensor for the given listener.

### Direct Channels
- `createDirectChannel(MemoryFile/HardwareBuffer)`: Creates a low-latency path for sensors to write directly to shared memory.

### Math Utilities
- `getRotationMatrix(...)`: Computes rotation and inclination matrices from gravity and geomagnetic vectors.
- `getOrientation(...)`: Computes azimuth, pitch, and roll from a rotation matrix.
- `remapCoordinateSystem(...)`: Rotates a rotation matrix to match a different screen orientation or application frame.

### Data Injection (Internal/Test)
- `initDataInjection(boolean)`: Enables a mode where the system ignores physical sensors and accepts injected data.

## Data Model
- **Delay Constants**: `SENSOR_DELAY_NORMAL`, `SENSOR_DELAY_UI`, `SENSOR_DELAY_GAME`, `SENSOR_DELAY_FASTEST`.
- **Status Constants**: `SENSOR_STATUS_ACCURACY_HIGH`, `MEDIUM`, `LOW`, `UNRELIABLE`.

## API Reference (Partial)
- `public abstract List<Sensor> getFullSensorList()`
- `public boolean registerListener(SensorEventListener listener, Sensor sensor, int samplingPeriodUs)`
- `public static boolean getRotationMatrix(float[] R, float[] I, float[] gravity, float[] geomagnetic)`

## Java-to-C++ Translation Guide
- **Abstraction**: `abstract class SensorManager` -> `class SensorManager` (Abstract Base).
- **Math**: The math utilities (`getRotationMatrix`, etc.) are implemented in Java but should be moved to a native SIMD-optimized library in C++.
- **Permissions**: C++ implementation must check for `android.permission.HIGH_SAMPLING_RATE_SENSORS` for rates > 200Hz.

## Implementation Risks
- **Power Management**: Sensors are a major battery drain. C++ code must ensure sensors are disabled when no longer needed.
- **Sampling Rates**: Hardware might deliver data at a different rate than requested; interpolation or decimation might be needed.
