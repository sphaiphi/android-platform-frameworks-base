# FaceSensorConfigurations - Reverse Engineering Documentation

## Executive Summary
`FaceSensorConfigurations` is a Parcelable class that holds configuration data for face sensors. It maps sensor instance names (AIDL or HIDL) to their `SensorProps`. It handles parsing HIDL configuration strings and AIDL instance names.

## Architecture Overview
- **Type**: Configuration Holder / Parcelable.
- **Usage**: Used to pass sensor configuration from `FaceService` or related setup components.

## Detailed Functionality
- **Map**: `mSensorPropsMap` maps instance name (`String`) to `SensorProps[]`.
- **AIDL Support**: `addAidlConfigs` adds placeholder entries.
- **HIDL Support**: `addHidlConfigs` parses config strings "id:modality:strength" and creates `HidlFaceSensorConfig` objects.
- **Virtual HAL**: `remapFqName` handles virtual HAL instance names ("virtual" -> "virtualhal.IVirtualHal").
- **Lazy Loading**: `getSensorPropForInstance` tries to fetch `IFace` (Binder) to get `SensorProps` if not already cached (for AIDL).

## Data Model
- `mResetLockoutRequiresChallenge`: `boolean`.
- `mSensorPropsMap`: `Map<String, SensorProps[]>`.

## Java-to-C++ Translation Guide
- **Parceling**: `writeMap` / `readHashMap`. C++ needs to handle the map serialization format used by Android Parcel.
- **Service Manager**: `getIFace` uses `ServiceManager.waitForService`. C++ equivalent is `android::IServiceManager::getService`.
- **Parsing**: Logic for parsing HIDL config strings (`split(":")`) needs to be ported.

## Implementation Risks
- **Binder Calls**: `getSensorPropForInstance` makes blocking Binder calls to HALs.

