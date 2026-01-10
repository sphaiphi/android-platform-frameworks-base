# FaceSensorProperties - Reverse Engineering Documentation

## Executive Summary
`FaceSensorProperties` is the public API version of face sensor properties. It extends `SensorProperties` and adds face-specific type information (RGB, IR).

## Architecture Overview
- **Inheritance**: Extends `android.hardware.biometrics.SensorProperties`.
- **Usage**: Returned by `FaceManager.getSensorProperties()`.

## Fields
- `mSensorType`: `TYPE_UNKNOWN` (0), `TYPE_RGB` (1), `TYPE_IR` (2).

## Java-to-C++ Translation Guide
- **Class**: C++ class inheriting from a `SensorProperties` base.
- **Conversion**: `from(FaceSensorPropertiesInternal)` static method logic.

