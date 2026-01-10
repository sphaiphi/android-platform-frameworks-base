# SensorEventListener - Reverse Engineering Documentation

## Executive Summary
`SensorEventListener` is the primary interface used by applications to receive sensor data and accuracy updates. It is the cornerstone of the Android sensor API.

## Architecture Overview
This is a standard callback interface. Implementing classes are registered with the `SensorManager`.

## Detailed Functionality

### `onSensorChanged(SensorEvent event)`
**Purpose**: Delivered when a new sensor reading is available.
**Java-Specific Notes**: The application does NOT own the `event` object. It may be part of a pool and reused immediately after the callback returns.
**C++ Implementation Guidance**: Pass by `const reference` to avoid copies, but emphasize that the data is transient.

### `onAccuracyChanged(Sensor sensor, int accuracy)`
**Purpose**: Delivered when the reliability of a sensor changes.
**Levels**: `UNRELIABLE`, `LOW`, `MEDIUM`, `HIGH`.

## Java-to-C++ Translation Guide
- **Interface**: `interface SensorEventListener` -> `class ISensorEventListener`.
- **Event Delivery**: Ensure the native dispatcher correctly handles thread synchronization when invoking these callbacks.

## Implementation Risks
- Reentrancy: Apps might try to unregister themselves inside the callback.
- Threading: Callbacks are typically delivered on the thread that registered the listener or a provided `Handler`.
