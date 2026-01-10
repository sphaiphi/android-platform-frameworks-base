# PerformanceHintManager - Reverse Engineering Documentation

## Executive Summary
`PerformanceHintManager` allows applications (primarily games) to send performance hints to the system, influencing CPU/GPU frequency and scheduling. It manages "Sessions" representing a workload on a group of threads.

## Architecture Overview
-   **Role**: Performance Tuning Client.
-   **Service**: `IHintManager`.
-   **Session**: Represents a workload. Created via `createHintSession`.

## Detailed Functionality
-   **`createHintSession(int[] tids, long targetDuration)`**: Registers a set of threads and a target completion time (deadline).
-   **`Session.reportActualWorkDuration(long actualDuration)`**: Feeds back the actual execution time. The system uses this to adjust clock speeds (PID loop) to meet the target duration efficiently.
-   **`Session.sendHint(int hint)`**: Sends immediate signals (CPU_LOAD_UP, CPU_LOAD_RESET).

## Java-to-C++ Translation Guide
-   **Binder**: `IHintManager`.
-   **Native**: This Java class wraps `nativeCreateSession`, `nativeReportActualWorkDuration`. The implementation is in `android_os_PerformanceHintManager.cpp` linking to `libandroid_runtime` and `libpowermanager`.
-   **NDK**: `APerformanceHint_createSession`.

## Implementation Risks
-   **Validation**: Invalid TIDs or durations throw exceptions.
-   **Session Lifetime**: Sessions must be closed (`close()`) to release resources.
