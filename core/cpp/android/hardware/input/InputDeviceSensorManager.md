# InputDeviceSensorManager - Reverse Engineering Documentation

## Executive Summary
`InputDeviceSensorManager` manages sensors found within input devices (like accelerometers in game controllers). It bridges `InputManager` events to the standard `SensorManager` / `SensorEventListener` paradigm.

## Architecture Overview
- **Manager**: Central registry of sensors for all input devices.
- **Delegation**: Creates `InputSensorManager` (subclass of `SensorManager`) for specific devices.
- **Listeners**: Manages `InputSensorEventListener` (AIDL callback) and dispatches events to registered local `SensorEventListener`s.
- **Thread Model**: Uses a dedicated `SensorThread` or provided `Handler`.

## Detailed Functionality

### Sensor Discovery
- **populateSensorsForInputDeviceLocked**: Fetches `InputSensorInfo[]` from service and converts them to `Sensor` objects.
- **onInputDeviceAdded/Changed/Removed**: Updates local cache `mSensors` (Map<deviceId, List<Sensor>>).

### Event Dispatch
- **InputSensorEventListener (Binder Stub)**: Receives `onInputSensorChanged` and `onInputSensorAccuracyChanged` from system server.
- **Delegates**: `InputSensorEventListenerDelegate` handles the mapping between the raw data and the `SensorEventListener` callback, running on the appropriate Looper.

### Sensor Registration
- **registerListenerInternal**: Registers the listener. If it's the first listener for this sensor, it calls `mGlobal.enableSensor` and `mGlobal.registerSensorListener`.
- **unregisterListenerInternal**: Unregisters. If no listeners remain for a sensor, it disables the sensor on the server.

### InputSensorManager (Inner Class)
- **Extends SensorManager**: Provides the standard API (`registerListener`, `getDefaultSensor`, etc.) but scoped to a specific `mId` (input device ID).
- **Unsupported Ops**: Direct channels, dynamic sensors, data injection are mostly no-ops or return false.

## Data Model
- `mSensors`: `Map<Integer, List<Sensor>>`.
- `mInputSensorEventListeners`: `ArrayList<InputSensorEventListenerDelegate>`.

## Java-to-C++ Translation Guide
- **SensorManager**: C++ Android NDK has `ASensorManager`. This class essentially emulates that behavior for Input Device sensors.
- **Threading**: Use `std::thread` or `ALooper` for event dispatch.
- **Events**: Convert raw float arrays to `ASensorEvent` structs.

## Implementation Risks
- **Concurrency**: Heavy use of `synchronized(mInputSensorLock)`. C++ must use `std::mutex`.
- **Lifecycle**: Ensuring listeners are unregistered to prevent leaks and battery drain (disabling sensors).

## Questions for C++ Team
- Does the C++ layer need to expose these as standard Android Sensors or just provide access to the data?
