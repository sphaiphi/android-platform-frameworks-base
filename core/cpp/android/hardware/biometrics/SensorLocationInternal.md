# SensorLocationInternal - Reverse Engineering Documentation

## Executive Summary
`SensorLocationInternal` describes the physical location of a biometric sensor relative to a display. It is crucial for Under-Display Fingerprint Sensors (UDFPS) to align the UI overlay with the hardware sensor.

## Detailed Functionality
- **Display ID**: `displayId` (String).
- **Coordinates**: `sensorLocationX`, `sensorLocationY` (pixels from top-left).
- **Size**: `sensorRadius` (pixels).
- **Rect**: `getRect()` helper.

## Java-to-C++ Translation Guide
- **Struct**: `struct SensorLocation { std::string displayId; int32_t x; int32_t y; int32_t radius; };`.

## Implementation Risks
- Multi-display devices (foldables) might have multiple locations for the same sensor (conceptually) or multiple sensors.
