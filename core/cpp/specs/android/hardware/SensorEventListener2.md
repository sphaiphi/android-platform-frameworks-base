# SensorEventListener2 - Reverse Engineering Documentation

## Executive Summary
`SensorEventListener2` is an extension of the standard `SensorEventListener` interface. It adds a specific callback for notification when a sensor FIFO flush operation has successfully completed.

## Architecture Overview
This interface inherits from `SensorEventListener`. It is used by the `SensorManager` to provide asynchronous feedback to applications that call `flush()`.

## Detailed Functionality

### `onFlushCompleted(Sensor sensor)`
**Purpose**: Notifies the application that all events in the hardware FIFO (at the time `flush()` was called) have been delivered to the listener.
**Behavior History**:
- **KitKat**: Notifications were sent even if other applications triggered the flush.
- **Lollipop+**: Notifications are sent ONLY to the application that explicitly requested the flush.
**Java-Specific Notes**: Part of the `android.hardware` package.

## Java-to-C++ Translation Guide
- **Interface**: `interface SensorEventListener2` -> `class ISensorEventListener2 : public ISensorEventListener`.
- **Callback**: Add `virtual void onFlushCompleted(const Sensor& sensor) = 0;`.

## Implementation Risks
- Ensuring strict delivery of flush completion events only to the requesting process/listener in C++.
