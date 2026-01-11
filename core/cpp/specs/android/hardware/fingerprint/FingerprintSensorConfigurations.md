# FingerprintSensorConfigurations - Reverse Engineering Documentation

## Executive Summary
`FingerprintSensorConfigurations` holds configuration data for fingerprint sensors, mapping instance names to `SensorProps`. It supports parsing HIDL configs and handling AIDL/Virtual HALs.

## Architecture Overview
- **Type**: Configuration Holder / Parcelable.
- **Usage**: Passing configuration to `FingerprintService`.

## Detailed Functionality
- **Map**: `mSensorPropsMap` maps instance name to `SensorProps[]`.
- **AIDL**: `addAidlSensors`.
- **HIDL**: `addHidlSensors`. Parses `HidlFingerprintSensorConfig`.
- **Virtual HAL**: `remapFqName` logic.
- **Lazy Loading**: `getSensorPropForInstance` fetches `IFingerprint` if needed.

## Data Model
- `mResetLockoutRequiresHardwareAuthToken`: `boolean`.
- `mSensorPropsMap`: `Map<String, SensorProps[]>`.

## Java-to-C++ Translation Guide
- **Parceling**: `writeMap` / `readHashMap`.
- **Binder**: `getIFingerprint` uses `ServiceManager.waitForService`.

