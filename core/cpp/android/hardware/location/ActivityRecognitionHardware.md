# ActivityRecognitionHardware - Reverse Engineering Documentation

## Executive Summary
`ActivityRecognitionHardware` is the Java-side implementation of the Activity Recognition Hardware Abstraction Layer (HAL) bridge. It acts as a singleton service wrapper that exposes native hardware capabilities to the framework via the `IActivityRecognitionHardware` Binder interface. It manages a list of "sinks" (listeners) and forwards events from the native layer to these sinks.

## Architecture Overview
- **Pattern**: Singleton / Adapter / Binder Service.
- **Inheritance**: Extends `IActivityRecognitionHardware.Stub`.
- **Native Binding**: heavily relies on JNI methods (`native*`) to interact with the actual hardware driver.
- **Observer Pattern**: Uses `RemoteCallbackList` (`SinkList`) to manage `IActivityRecognitionHardwareSink` observers.

## Detailed Functionality

### Initialization
- **Singleton**: Access via `getInstance(Context)`.
- **Construction**:
    1.  Calls `nativeInitialize()`.
    2.  Fetches supported activities via `nativeGetSupportedActivities()`.
    3.  Initializes internal tracking arrays for enabled events.

### event Management
- **Enable/Disable**: Forwards requests to `nativeEnableActivityEvent` / `nativeDisableActivityEvent`. Tracks state in `mSupportedActivitiesEnabledEvents`.
- **Broadcasting**: `onActivityChanged(Event[])` is called from native code. It wraps the raw data into `ActivityChangedEvent` and broadcasts it to all registered sinks.

### Native Interface (JNI)
- `nativeInitialize()`
- `nativeRelease()`
- `nativeIsSupported()`
- `nativeGetSupportedActivities()`
- `nativeEnableActivityEvent(int type, int eventType, long latency)`
- `nativeDisableActivityEvent(int type, int eventType)`
- `nativeFlush()`

## Data Model
### Internal `Event` Class (private static)
Used for JNI array passing.
| Field | Type | Description |
|---|---|---|
| `activity` | `int` | Index into `mSupportedActivities`. |
| `type` | `int` | Event type. |
| `timestamp` | `long` | Timestamp. |

### Helper State
- `mSupportedActivities`: `String[]`.
- `mSupportedActivitiesEnabledEvents`: `int[][]` (State tracking).

## Java-to-C++ Translation Guide
### Architecture Mapping
This class **is** the bridge to C++. Re-implementing this in C++ typically means implementing the `IActivityRecognitionHardware` AIDL interface directly in a C++ service (e.g., in `system/hardware/interfaces` or similar).

- **Binder Interface**: `IActivityRecognitionHardware.aidl` -> `BnActivityRecognitionHardware`.
- **Logic**: The JNI logic here would become direct calls to the hardware/HAL implementation.

### Key logic to Preserve
- **Sink Management**: The `RemoteCallbackList` logic handles client death (binder died). The C++ implementation must use `linkToDeath` on registered callbacks to clean up resources (disable events) if a client crashes.
- **Permission Checks**: `checkPermissions` enforces `Manifest.permission.LOCATION_HARDWARE`.

## Questions for C++ Team
- Is this legacy code being replaced by a pure AIDL HAL service, or is this the permanent adapter for legacy HALs?
