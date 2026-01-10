# SensorPrivacyManager - Reverse Engineering Documentation

## Executive Summary
`SensorPrivacyManager` provides a mechanism to globally toggle privacy for sensitive sensors like the microphone and camera. It allows querying the privacy state, registering for state changes, and (for system apps) controlling the privacy toggles.

## Architecture Overview
This is a `SystemService` proxying the `ISensorPrivacyManager` AIDL interface. It supports both software-based toggles (user-controlled) and hardware-based toggles (physical switches).

## Detailed Functionality

### Privacy Toggles
- **Sensors**: `MICROPHONE` (1), `CAMERA` (2).
- **Toggle Types**: `SOFTWARE` (1), `HARDWARE` (2).
- **States**: `ENABLED` (1), `DISABLED` (2), `ENABLED_EXCEPT_ALLOWLISTED_APPS` (3).

### Monitoring
- `addSensorPrivacyListener(...)`: Registers a callback to be notified when privacy state changes for a specific sensor or toggle type.
- `mIToggleListener`: A singleton native listener (`ISensorPrivacyListener.Stub`) that dispatches events to multiple Java-level listeners.

### Control (System/Permissioned)
- `setSensorPrivacy(boolean)`: Enables or disables global privacy.
- `setCameraPrivacyAllowlist(List<String>)`: Defines automotive driver-assistance apps that can bypass camera privacy.

## Data Model
- `ToggleSupportCache`: Caches whether a specific toggle type/sensor combination is supported on the hardware.

## API Reference
- `public boolean supportsSensorToggle(int sensor)`
- `public boolean isSensorPrivacyEnabled(int sensor)`
- `public void addSensorPrivacyListener(int sensor, OnSensorPrivacyChangedListener listener)`

## Java-to-C++ Translation Guide
- **Singleton**: The Java class uses a thread-safe singleton pattern (`getInstance`). C++ should use a similar approach or a managed service reference.
- **Cache**: `mToggleSupportCache` (ArrayMap) -> `std::map<std::pair<int, int>, bool>`.
- **Listeners**: Use a thread-safe vector of observers.

## Implementation Risks
- Security: Privacy toggles are high-stakes. The C++ implementation must be extremely robust against IPC spoofing.
- Hardware Sync: Ensuring the software state correctly reflects physical switch positions (hardware toggles).
