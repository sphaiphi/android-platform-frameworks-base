# FingerprintSensorProperties - Reverse Engineering Documentation

## Executive Summary
`FingerprintSensorProperties` is the public API version of fingerprint sensor properties. It extends `SensorProperties` and adds fingerprint-specific types (Rear, UDFPS, Power Button, etc.).

## Architecture Overview
- **Inheritance**: Extends `android.hardware.biometrics.SensorProperties`.
- **Usage**: Returned by `FingerprintManager.getSensorProperties()`.

## Fields
- `mSensorType`: `TYPE_UNKNOWN` (0), `TYPE_REAR` (1), `TYPE_UDFPS_ULTRASONIC` (2), `TYPE_UDFPS_OPTICAL` (3), `TYPE_POWER_BUTTON` (4), `TYPE_HOME_BUTTON` (5).

## Java-to-C++ Translation Guide
- **Class**: C++ class inheriting from `SensorProperties` base.
- **Conversion**: `from(FingerprintSensorPropertiesInternal)`.

