# ApplicationErrorReport - Reverse Engineering Documentation

## Executive Summary
`ApplicationErrorReport` is a Parcelable class used to describe an application error (crash, ANR, battery usage, etc.) to be reported to the system or installer.

## Architecture Overview
*   **Type**: Parcelable Data Class.
*   **Nested Classes**: `CrashInfo`, `AnrInfo`, `BatteryInfo`, `RunningServiceInfo`.

## Detailed Functionality
*   **Types**: Defines constants for `TYPE_CRASH`, `TYPE_ANR`, `TYPE_BATTERY`, `TYPE_RUNNING_SERVICE`.
*   **Fields**: `packageName`, `installerPackageName`, `processName`, `time`, `systemApp`.
*   **Payloads**: Contains specific info objects based on the type.

### CrashInfo
*   Captures exception class, message, file, method, line number, and stack trace.
*   Can sanitize stack traces (truncate).

### AnrInfo
*   Captures activity name, cause, and info string (CPU stats).

### BatteryInfo / RunningServiceInfo
*   Usage details, duration, checkin details.

## API Reference
*   `getErrorReportReceiver(Context, String, int)`: Finds the component to handle the error report (system app or installer).

## Java-to-C++ Translation Guide
*   **Serialization**: Implement `Parcelable` read/write logic.
*   **Exception Parsing**: `CrashInfo(Throwable)` constructor parses Java exceptions. C++ equivalent would need to parse C++ exceptions or log dumps.

## Implementation Risks
*   **Data Size**: Crash reports can be large; Binder limits apply. Use `Binder.CHECK_PARCEL_SIZE` equivalent checks.
