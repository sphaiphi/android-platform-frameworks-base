# HidlFingerprintSensorConfig - Reverse Engineering Documentation

## Executive Summary
`HidlFingerprintSensorConfig` parses HIDL-style configuration strings into `SensorProps` (AIDL format).

## Architecture Overview
- **Inheritance**: Extends `android.hardware.biometrics.fingerprint.SensorProps`.
- **Usage**: Used by `FingerprintSensorConfigurations`.

## Detailed Functionality
- **Parsing**: `parse(String config, Context context)`.
    - Format: `id:modality:strength`.
    - Determines sensor type (UDFPS, Power Button, Rear) based on config resources (`R.array.config_udfps_sensor_props`, `R.bool.config_is_powerbutton_fps`).
    - Sets up `sensorLocations` (UDFPS props or workaround props or default).

## Java-to-C++ Translation Guide
- **Resources**: Heavily dependent on `Context.getResources()` to determine sensor type and location. Porting requires access to system configuration.

