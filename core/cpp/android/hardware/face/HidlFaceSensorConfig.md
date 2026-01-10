# HidlFaceSensorConfig - Reverse Engineering Documentation

## Executive Summary
`HidlFaceSensorConfig` is a helper class to parse HIDL-style configuration strings into `SensorProps` (AIDL format). This bridges the gap between legacy HIDL config formats and the modern AIDL infrastructure.

## Architecture Overview
- **Inheritance**: Extends `android.hardware.biometrics.face.SensorProps` (AIDL generated class).
- **Usage**: Used by `FaceSensorConfigurations`.

## Detailed Functionality
- **Parsing**: `parse(String config, Context context)`:
    - Format: `id:modality:strength`.
    - Maps strength integer to `SensorStrength` byte (CONVENIENCE, WEAK, STRONG).
    - Fetches resources (`R.bool.config_faceAuthSupportsSelfIllumination`, `R.integer.config_faceMaxTemplatesPerUser`) to fill in `commonProps`.

## Java-to-C++ Translation Guide
- **Parsing**: String parsing logic.
- **Resources**: Needs access to system configuration/resources to populate max enrollments and self-illumination flags.

