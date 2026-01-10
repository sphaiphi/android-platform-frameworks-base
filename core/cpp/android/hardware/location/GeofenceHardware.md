# GeofenceHardware - Reverse Engineering Documentation

## Executive Summary
`GeofenceHardware` is the public API surface for hardware-accelerated geofencing. It allows applications (with permissions) to add, remove, pause, and resume geofences monitored by hardware subsystems (GPS, Fused).

## Architecture Overview
- **Pattern**: Proxy / Facade.
- **Role**: Main entry point for hardware geofencing.
- **Dependencies**: `IGeofenceHardware` (Binder service).

## Detailed Functionality

### Constants
- **Monitoring Types**: `MONITORING_TYPE_GPS_HARDWARE`, `MONITORING_TYPE_FUSED_HARDWARE`.
- **Status**: `MONITOR_CURRENTLY_AVAILABLE`, etc.
- **Transitions**: `GEOFENCE_ENTERED`, `EXITED`, `UNCERTAIN`.
- **Sources**: `SOURCE_TECHNOLOGY_GNSS`, `WIFI`, etc.

### Operations
- `addGeofence(...)`: Wraps request in `GeofenceHardwareRequestParcelable` and `GeofenceHardwareCallbackWrapper` before calling service.
- `removeGeofence`, `pauseGeofence`, `resumeGeofence`.
- `registerForMonitorStateChangeCallback`: Monitors hardware availability.

### Callback Wrapping
- Wraps user provided `GeofenceHardwareCallback` and `GeofenceHardwareMonitorCallback` into internal inner classes (`GeofenceHardwareCallbackWrapper`, etc.) which extend the AIDL Stub classes. This handles the IPC callback mechanism.

## Data Model
- `mService`: `IGeofenceHardware`.
- `mCallbacks`: `HashMap` (Mapping user callbacks to Binder wrappers).

## Java-to-C++ Translation Guide
### Architecture Mapping
- **C++ Class**: `GeofenceHardware`.
- **Binder**: Wraps `sp<IGeofenceHardware>`.
- **Callbacks**: Needs a mechanism to wrap C++ callbacks into `BnGeofenceHardwareCallback` objects to pass to Binder.

## Questions for C++ Team
- Is this API intended to be exposed in the NDK? (Currently `@SystemApi`).
