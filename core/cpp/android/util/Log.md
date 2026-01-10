# Log - Reverse Engineering Documentation

## Executive Summary
Android's central logging API. Sends log messages to the system log buffers (Main, Radio, Events, System, Crash).

## Architecture Overview
*   **Native Bridge**: Most heavy lifting is done via JNI calls (`println_native`).
*   **Priorities**: VERBOSE (2) to ASSERT (7).
*   **WTF**: "What a Terrible Failure" - handles critical errors, potentially terminating the process or sending reports.

## Key Algorithms
*   **`println_native`**: Writes to the kernel log driver (or user-space logger deamon `logd`).
*   **`isLoggable`**: Checks system properties (`log.tag.<TAG>`) to determine if a specific tag/level should be logged. Cached by native layer usually.
*   **`printlns`**: Handles splitting long log messages that exceed the kernel buffer size (approx 4KB).

## Java-to-C++ Translation Guide
*   **liblog**: Android has a native library `liblog` (`android/log.h`). The Java `Log` class is essentially a wrapper around `__android_log_print` and related functions.
*   **Implementation**: In C++, use `<android/log.h>` directly.

## Implementation Risks
*   **Performance**: Logging is relatively expensive (IPC/Syscall). `isLoggable` checks help.
