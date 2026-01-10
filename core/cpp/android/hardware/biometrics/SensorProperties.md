# SensorProperties - Reverse Engineering Documentation

## Executive Summary
`SensorProperties` is the public-facing class containing modality-agnostic properties of a biometric sensor. It exposes the sensor ID, strength, and component info.

## Detailed Functionality

### Strength Constants
- `STRENGTH_CONVENIENCE` (0)
- `STRENGTH_WEAK` (1)
- `STRENGTH_STRONG` (2)

### Component Info
Nested `ComponentInfo` class:
- `componentId`, `hardwareVersion`, `firmwareVersion`, `serialNumber`, `softwareVersion`.

### Constructor
Created from `SensorPropertiesInternal`.

## Java-to-C++ Translation Guide
- **Struct**: `struct SensorProperties`.
- **Mapping**: Map `SensorPropertiesInternal` (internal AIDL object) to this public representation.

## Implementation Risks
- None.
