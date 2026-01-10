# TimeZoneDetector - Reverse Engineering Documentation

## Executive Summary
`TimeZoneDetector` is the client-side interface for the Time Zone Detector service. It defines shell command constants and methods for components to inject time zone suggestions.

## Architecture Overview
- **Interface**: `TimeZoneDetector`
- **System Service**: `@SystemService(Context.TIME_ZONE_DETECTOR_SERVICE)`
- **Usage**: Implemented by `TimeZoneDetectorImpl` (proxy) and the service implementation itself.

## Detailed Functionality

### Shell Command Constants
Extensive list of string constants for `adb shell cmd time_zone_detector ...`.
- `SHELL_COMMAND_SUGGEST_MANUAL_TIME_ZONE`
- `SHELL_COMMAND_SUGGEST_TELEPHONY_TIME_ZONE`
- `SHELL_COMMAND_ENABLE_TELEPHONY_FALLBACK`
- ... (See source for full list).

### Static Utility
- **`createManualTimeZoneSuggestion(String tzId, String debugInfo)`**: Helper to create a manual suggestion quickly.

### Core Methods
1.  **`suggestManualTimeZone(ManualTimeZoneSuggestion)`**
    - **Permission**: `SUGGEST_MANUAL_TIME_AND_ZONE`
    - **Returns**: `boolean` (success/failure).
2.  **`suggestTelephonyTimeZone(TelephonyTimeZoneSuggestion)`**
    - **Permission**: `SUGGEST_TELEPHONY_TIME_AND_ZONE`
    - **Returns**: `void` (fire and forget).

## API Reference
See Core Methods.

## Java-to-C++ Translation Guide

### Interface
- **Java**: Interface.
- **C++**: Abstract base class.

### Constants
- Define these strings in a shared header for the C++ CLI tool to use.

## Test Cases & Validation
- **Permissions**: Verify calls fail without permissions.

## Implementation Risks
- **Shell Protocol**: Any C++ implementation of the shell command handler must support these exact string verbs to remain compatible with existing tools.
