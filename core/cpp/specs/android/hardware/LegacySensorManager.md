# LegacySensorManager - Reverse Engineering Documentation

## Executive Summary
`LegacySensorManager` is a hidden (`@hide`) helper class used to provide backward compatibility for the deprecated `SensorListener` and related APIs. It maps legacy sensor events and constants to the modern `SensorEventListener` system.

## Architecture Overview
This class wraps a modern `SensorManager` and maintains a mapping of legacy `SensorListener` objects to `LegacyListener` objects. It handles coordinate system transformations and filtering required by older Android applications.

## Detailed Functionality

### Coordinate Mapping
`mapSensorDataToWindow(int sensor, float[] values, int orientation)`:
- **Purpose**: Converts sensor data from the device's coordinate space to the window's coordinate space based on screen rotation.
- **Logic**: Inverts axes for orientation, accelerometer, and magnetic field sensors. Rotates values by 90, 180, or 270 degrees as needed.

### Event Filtering
`LmsFilter`:
- **Purpose**: A Least Mean Squares (LMS) filter specifically for the Azimuth (Yaw) value of the orientation sensor.
- **Logic**: Implements a circular buffer and performs linear prediction to smooth out noise in the compass data.

### Listener Wrapping
`LegacyListener` (inner class):
- Implements `SensorEventListener`.
- Receives events from the modern system, applies coordinate transformations, filters orientation data, and dispatches to the legacy `SensorListener.onSensorChanged`.

## Data Model
- **Legacy Sensor IDs**: `SENSOR_ORIENTATION`, `SENSOR_ACCELEROMETER`, `SENSOR_MAGNETIC_FIELD`, etc.
- **Mapping**: `HashMap<SensorListener, LegacyListener> mLegacyListenersMap`.

## API Reference (Internal)
- `public int getSensors()`
- `public boolean registerListener(SensorListener listener, int sensors, int rate)`
- `public void unregisterListener(SensorListener listener, int sensors)`

## Java-to-C++ Translation Guide
- **Filtering**: The `LmsFilter` logic can be ported to C++ using `std::deque` or a fixed-size array for the circular buffer.
- **Synchronization**: `synchronized (SensorManager.class)` and `synchronized (mLegacyListenersMap)` should map to `std::mutex` or `std::recursive_mutex`.

## Implementation Risks
- Complexity of coordinate transformations for various screen rotations.
- Maintaining exact behavior of the legacy LMS filter to avoid breaking older apps that rely on its specific smoothing characteristics.
