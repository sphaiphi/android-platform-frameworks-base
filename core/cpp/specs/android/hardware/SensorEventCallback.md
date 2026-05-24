# SensorEventCallback - Reverse Engineering Documentation

## Executive Summary
`SensorEventCallback` is an abstract class that extends `SensorEventListener2` and adds support for receiving `SensorAdditionalInfo`. It provides empty default implementations for all methods, allowing developers to override only the ones they need.

## Architecture Overview
It sits at the top of the sensor listener hierarchy, combining standard sensor data delivery, flush completion notifications, and additional metadata frames.

## Detailed Functionality

### Methods
- `onSensorChanged(SensorEvent)`: Standard data updates.
- `onAccuracyChanged(Sensor, int)`: Accuracy changes.
- `onFlushCompleted(Sensor)`: Asynchronous notification after `SensorManager.flush()`.
- `onSensorAdditionalInfo(SensorAdditionalInfo)`: Metadata frames (calibration, placement, etc.).

## Java-to-C++ Translation Guide
- **Class**: `abstract class SensorEventCallback` -> `class ISensorEventCallback` (Interface or abstract class with virtual methods).
- **Default Implementations**: C++ interfaces can provide default `{}` implementations for virtual methods to achieve the same convenience.

## Implementation Risks
- Performance: `onSensorChanged` is called very frequently. C++ overhead must be minimal.
