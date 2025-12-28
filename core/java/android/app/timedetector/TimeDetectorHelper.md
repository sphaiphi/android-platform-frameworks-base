# TimeDetectorHelper - Reverse Engineering Documentation

## Executive Summary
`TimeDetectorHelper` is a utility singleton containing fundamental time detection logic that relies on hard-coded facts or SDK APIs, avoiding Binder calls. It primarily manages bounds checking for valid time suggestions, specifically handling the Y2038 problem (32-bit time_t overflow).

## Architecture Overview
- **Class**: `TimeDetectorHelper`
- **Pattern**: Singleton (`INSTANCE` field).
- **Scope**: Used by both client (UI) and server (validation) code.

## Detailed Functionality

### Constants (Hard-coded facts)
- `MANUAL_SUGGESTION_YEAR_MIN`: 2015.
- `MANUAL_SUGGESTION_LOWER_BOUND`: Nov 5, 2014 (calculated from year min logic).
- `MANUAL_SUGGESTION_YEAR_MAX_WITHOUT_Y2038_ISSUE`: 2100.
- `MANUAL_SUGGESTION_YEAR_MAX_WITH_Y2038_ISSUE`: 2037 (to avoid crossing Jan 19, 2038).

### Y2038 Detection
**Method**: `getDeviceHasY2038Issue()`
**Logic**: Checks `Build.SUPPORTED_32_BIT_ABIS.length > 0`.
**Interpretation**: If the device supports any 32-bit ABI, it is assumed to have potential signed 32-bit `time_t` issues, imposing strict upper bounds on time setting.

### Suggestion Bounds
1.  **Manual Lower Bound**: Fixed at `MANUAL_SUGGESTION_LOWER_BOUND` (Nov 2014).
2.  **Auto Lower Bound**: Defaults to `max(System Partition Mod Time, Build Time)`.
3.  **Upper Bound**:
    - If Y2038 issue exists: ~Jan 2038 (`Integer.MAX_VALUE` seconds).
    - If no issue: ~Infinity (`Long.MAX_VALUE` millis).

### Date Selection limits (UI)
- `getManualDateSelectionYearMin()`: Returns 2015.
- `getManualDateSelectionYearMax()`: Returns 2037 or 2100 based on Y2038 check.

## Java-to-C++ Translation Guide

### Singleton
- **Java**: Static final `INSTANCE`.
- **C++**: `static TimeDetectorHelper& getInstance()`.

### Build Properties
- **Java**: Accesses `android.os.Build` and `Environment`.
- **C++**: Need equivalent access to system properties (`ro.product.cpu.abilist32`?) and filesystem stats (`stat` for directory modification time).

### Time Math
- **Java**: uses `java.time.Instant`.
- **C++**: Use `std::chrono::system_clock` or simple `int64_t` milliseconds arithmetic. Be careful with overflow checking.

### Y2038 Logic
- **Critical**: C++ implementation must correctly detect the architecture capabilities. If the C++ code itself is 64-bit but the system supports 32-bit apps, the constraint applies.

## Test Cases & Validation
- **Y2038 Check**: Verify on 32-bit vs 64-only devices.
- **Lower Bound**: Verify manual lower bound is constant.

## Implementation Risks
- **Build Property Access**: C++ access to `Build.SUPPORTED_32_BIT_ABIS` might require reading system properties directly.
- **Environment**: Accessing `rootDirectory` timestamp in C++ requires correct permissions (SELinux).
