# TimeDetector - Reverse Engineering Documentation

## Executive Summary
`TimeDetector` is the client-side interface (and system service definition) for interacting with the `TimeDetectorService`. It defines constants for shell commands and provides methods for components (like Telephony or Settings) to suggest times.

## Architecture Overview
- **Interface**: `TimeDetector`
- **Annotations**: `@SystemService(Context.TIME_DETECTOR_SERVICE)` indicates it's a registered system service.
- **Role**: Entry point for sending time signals to the system.

## Detailed Functionality

### Shell Command Constants
Defines string constants used by `TimeDetectorShellCommand` (implied) to interact with the service via `adb shell cmd time_detector`.
- `SHELL_COMMAND_SUGGEST_MANUAL_TIME`
- `SHELL_COMMAND_SUGGEST_TELEPHONY_TIME`
- `SHELL_COMMAND_GET_TIME_STATE`
- ...and others.

### Static Utility
`createManualTimeSuggestion(long when, String why)`
- **Purpose**: Helper to create a `ManualTimeSuggestion` using current `SystemClock.elapsedRealtime()`.
- **Algorithm**: Capture current realtime, create `UnixEpochTime` with `when` (target wall clock), wrap in `ManualTimeSuggestion`.

### Interface Methods
1.  **`suggestTelephonyTime(TelephonyTimeSuggestion)`**
    - **Permission**: `android.Manifest.permission.SUGGEST_TELEPHONY_TIME_AND_ZONE`
    - **Purpose**: Feed NITZ signal to detector.
2.  **`suggestManualTime(ManualTimeSuggestion)`**
    - **Permission**: `android.Manifest.permission.SUGGEST_MANUAL_TIME_AND_ZONE`
    - **Purpose**: Feed user settings signal to detector.
    - **Returns**: `boolean` (accepted/rejected).

## API Reference
See Interface Methods above.

## Java-to-C++ Translation Guide

### Interface Definition
- **Java**: `interface TimeDetector`.
- **C++**: Abstract base class (virtual destructor, pure virtual methods).
- **IPC**: This interface effectively mirrors part of the AIDL. The C++ client would likely wrap an `sp<ITimeDetectorService>` binder proxy.

### Constants
- **Java**: `static final String`.
- **C++**: `static constexpr const char*` in a header file.

## Test Cases & Validation
- **Permission Checks**: Implementation must verify permissions (usually server-side). Client-side tests verify `SecurityException` is propagated.

## Implementation Risks
- **Shell Command Parity**: Ensure string constants match those expected by the shell command parser in the service.
