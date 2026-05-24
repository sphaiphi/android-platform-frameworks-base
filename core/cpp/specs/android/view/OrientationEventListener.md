# OrientationEventListener - Reverse Engineering Documentation

## Executive Summary
`OrientationEventListener` provides a high-level helper for receiving notifications from the `SensorManager` when the orientation of the device changes. it abstracts the raw accelerometer data into a simple integer degree value (0-359).

## Architecture Overview
*   **Role**: Sensor-to-Orientation translator.
*   **Dependency**: `SensorManager`.
*   **Algorithm**: Uses the Arc-Tangent of the X and Y gravitational components to calculate the tilt angle.

## Detailed Functionality

### 1. Orientation Calculation
*   **`onSensorChanged()`**: Receives 3-axis accelerometer data.
*   **Magnitude Check**: Ensures the device is not "flat" (where orientation is ambiguous) by checking the magnitude of gravity on the X-Y plane relative to the Z-axis.
*   **Degrees**: Returns 0 for natural (portrait), 90 for left-side up, 180 for upside-down, and 270 for right-side up.

### 2. Control
*   **`enable()` / `disable()`**: Registers/unregisters the sensor listener to save power.

### 3. Compatibility
*   **`CompatSensorEventListenerImpl`**: Adjusts reported orientation values if the system has applied a display rotation override (e.g., for camera compatibility mode).

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Wrap `ASensorManager` and `ASensorEventQueue`.
*   **Math**: Use `atan2f` from `cmath`.

## Implementation Risks
*   **Battery Drain**: Forgetting to `disable()` the listener will keep the accelerometer active indefinitely.
*   **Jitter**: Raw sensor data can be noisy; the implementation should ideally include some hysteresis or low-pass filtering.
