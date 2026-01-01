# SystemSensorManager - Reverse Engineering Documentation

## Executive Summary
`SystemSensorManager` is the concrete implementation of `SensorManager` that communicates with the built-in system sensors. It handles the low-level JNI interaction, event queue management, and listener dispatching.

## Architecture Overview
The class acts as a central hub for sensor activities. It manages:
1. **Sensor Lists**: Static and dynamic sensor discovery.
2. **Event Queues**: `SensorEventQueue` and `TriggerEventQueue` for standard and one-shot sensors.
3. **Dispatching**: Distributes events from the native layer to Java listeners on appropriate loopers.
4. **Data Injection**: Manages an `InjectEventQueue` for testing.

## Detailed Functionality

### Initialization
- Calls `nativeClassInit()` and `nativeCreate()`.
- Iterates through all default device sensors using `nativeGetDefaultDeviceSensorAtIndex`.

### Event Management
- **BaseEventQueue**: An abstract inner class that manages a native event queue (`mNativeSensorEventQueue`).
- **SensorEventQueue**: Specialized for `SensorEventListener`. Handles `dispatchSensorEvent`, `dispatchFlushCompleteEvent`, and `dispatchAdditionalInfoEvent`.
- **TriggerEventQueue**: Specialized for `TriggerEventListener`. Automatically cancels after one event.

### Runtime and Virtual Sensors
- Handles sensors from `VirtualDeviceManager` (`onVirtualDeviceClosed`).
- Uses `nativeGetRuntimeSensors` to fetch sensors for specific device IDs.

### Capping and Permissions
- Enforces sampling rate limits (200Hz) if `HIGH_SAMPLING_RATE_SENSORS` permission is missing for specific sensor types (Accelerometer, Gyroscope, Magnetometer).

## Data Model
- `mHandleToSensor`: Mapping from integer handles to `Sensor` objects.
- `mSensorListeners`: Mapping from listeners to their respective event queues.

## Java-to-C++ Translation Guide
- **Threading**: Each `BaseEventQueue` is associated with a `Looper`. C++ implementation should use `ALooper` and a file descriptor-based event signaling.
- **Native Instance**: `mNativeInstance` (long) points to a native `SensorManager` C++ object.
- **Permissions**: Must integrate with the system's permission checking service.

## Implementation Risks
- High-frequency interrupt handling: `dispatchSensorEvent` is called from native code and must be highly efficient.
- Consistency: Ensuring Java `Sensor` objects and native sensor descriptors remain synchronized.
