# BrightnessChangeEvent - Reverse Engineering Documentation

## Executive Summary
`BrightnessChangeEvent` is a Parcelable data object that records a snapshot of device state at the moment a brightness change occurred. It is used for metrics, adaptive brightness learning, and debugging. It captures lux (ambient light), timestamps, package name, battery level, color temperature, and color histograms.

## Architecture Overview
- **Type**: Immutable Data Object / Parcelable
- **Package**: `android.hardware.display`
- **Builder Pattern**: Uses a static `Builder` class for construction.

## Detailed Functionality

### captured Data
- **Event Info**: `brightness` (nits), `timeStamp`.
- **Context**: `packageName` (app in foreground), `userId`.
- **Device State**:
    - `uniqueDisplayId`
    - `batteryLevel`
    - `nightMode` (boolean)
    - `colorTemperature` (Kelvin)
    - `reduceBrightColors` (boolean + strength/offset)
- **Sensor Data**: `luxValues` and `luxTimestamps` (recent history).
- **Color Sampling**: `colorValueBuckets` (HSV value component histogram) and `colorSampleDuration`.

## Data Model
All fields are `public final`.
- **Scalars**: `float`, `long`, `int`, `boolean`.
- **Arrays**: `float[]`, `long[]` (Lux history and Color buckets).
- **Strings**: `packageName`, `uniqueDisplayId`.

## Java-to-C++ Translation Guide
- **Parcelable**: Straightforward mapping.
- **Nullable Fields**: `packageName`, `colorValueBuckets` can be null (handled via flags or size checks in Parcel).
- **Arrays**: Use `std::vector`.
- **Builder**: C++ builder pattern can be replicated or just use a struct with designated initializers if C++20 is allowed.

### Serialization Notes
- `colorValueBuckets` serialization:
    - Java: `dest.writeLongArray(colorValueBuckets)`
    - If null, `writeLongArray` handles it? *Check:* `Parcel.writeLongArray` writes length -1 if null.
- `packageName` redaction logic exists in copy constructor (`redactPackage` bool).

## API Reference
- `BrightnessChangeEvent(Parcel source)`: Deserialization.
- `writeToParcel(...)`: Serialization.
- `Builder`: Setters for all fields.
