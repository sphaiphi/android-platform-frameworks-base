# InputSensorInfo - Reverse Engineering Documentation

## Executive Summary
`InputSensorInfo` is a Parcelable data class containing static metadata about a sensor found on an input device (e.g., resolution, max range, power usage).

## Architecture Overview
- **Parcelable**: Generated via `DataClass`.
- **Immutable**: Fields are final/private with getters.

## Detailed Functionality
Stores standard sensor properties:
- Name, Vendor, Version, Handle, Type
- MaxRange, Resolution, Power, MinDelay
- FIFO counts
- String Type, Required Permission
- MaxDelay, Flags, Id

## Data Model
- Primitives (`int`, `float`) and `Strings`.

## Java-to-C++ Translation Guide
- **Struct**: Plain Old Data (POD) struct + Strings.
- **AIDL**: Matches `android.hardware.input.InputSensorInfo` AIDL definition.

## Implementation Risks
- None.
