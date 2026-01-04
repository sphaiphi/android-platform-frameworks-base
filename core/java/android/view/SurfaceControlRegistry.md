# SurfaceControlRegistry - Reverse Engineering Documentation

## Executive Summary
`SurfaceControlRegistry` is a diagnostic utility used to track all active `SurfaceControl` instances within a process. it is designed to help developers identify "Surface Leaks" (layers that are created but never released) by monitoring the count of active surfaces and providing detailed reports when thresholds are exceeded.

## Architecture Overview
*   **Role**: Native resource leak detector.
*   **Storage**: Uses a `WeakHashMap` to track `SurfaceControl` objects without preventing their garbage collection.
*   **Thresholds**: Triggers a report when the number of active layers exceeds a limit (default: 1024).

## Detailed Functionality

### 1. Leak Detection
*   **`add()`** / **`remove()`**: Tracks the lifetime of surface controls.
*   **`Reporter`**: Interface for processing the list of leaked surfaces (default implementation logs to logcat).

### 2. Call Stack Debugging
*   **`sCallStackDebuggingEnabled`**: Allows logging the exact stack trace of every `SurfaceControl.Transaction` call for a specific layer name or method.

## Java-to-C++ Translation Guide
*   **Mechanism**: C++ implementation should use a global registry of `wp<SurfaceControl>` objects.
*   **Stack Traces**: Requires integration with a native backtrace library (e.g., `libbacktrace` or `libunwindstack`).

## Implementation Risks
*   **Performance**: If stack debugging is enabled globally, it will severely impact rendering performance due to the overhead of generating traces for every transaction.
*   **Permission**: Creating the process instance requires the `READ_FRAME_BUFFER` permission.
