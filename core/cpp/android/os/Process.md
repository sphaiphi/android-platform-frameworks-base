# Process - Reverse Engineering Documentation

## Executive Summary
`Process` provides tools for managing OS processes, including UID/GID constants, process starting (via Zygote), signal sending, and thread priority management. It serves as the primary interface between the Android framework and the underlying Linux process model.

## Architecture Overview
-   **Role**: Process Management Utility.
-   **Native Peer**: `android_util_Process.cpp` (JNI).
-   **Key Dependencies**: `ZygoteProcess` (for spawning apps).

## Data Model

### Constants
-   **UIDs**: `SYSTEM_UID` (1000), `PHONE_UID` (1001), `SHELL_UID` (2000), `WIFI_UID` (1010), etc.
-   **Ranges**: `FIRST_APPLICATION_UID` (10000), `LAST_APPLICATION_UID` (19999).
-   **Priorities**: `THREAD_PRIORITY_DEFAULT` (0), `THREAD_PRIORITY_BACKGROUND` (10), `THREAD_PRIORITY_FOREGROUND` (-2).

### Zygote Connection
-   `ZYGOTE_PROCESS`: Static instance of `ZygoteProcess` used to fork new applications via socket communication.

## Detailed Functionality

### Process Lifecycle
-   **`start(...)`**: Asks the Zygote to fork a new process. Arguments include class name, UID, GID, mount flags, etc.
-   **`killProcess(int pid)`**: Sends `SIGKILL`.
-   **`sendSignal(int pid, int signal)`**: Sends arbitrary signals.

### Thread Management
-   **`setThreadPriority(int tid, int priority)`**: Maps Android priority (-20 to 19) to Linux nice values.
-   **`getThreadPriority(int tid)`**: Reads nice value.
-   **`setThreadGroup(int tid, int group)`**: Moves threads between cgroups (e.g. background/foreground cpuset).

### Identity
-   **`myPid()`, `myTid()`, `myUid()`**: Wrappers for `getpid`, `gettid`, `getuid`.
-   **`isIsolated()`, `isSdkSandbox()`**: Checks if the current process is sandboxed based on UID ranges.

## Java-to-C++ Translation Guide
-   **Equivalent**: `cutils/process_name.h`, `utils/Thread.h`.
-   **UIDs**: Defined in `libcutils/include/private/android_filesystem_config.h` (AID_SYSTEM, AID_RADIO, etc.). C++ code should use these headers.
-   **Priority**: Use `setpriority` (standard Linux) or `androidSetThreadPriority` (cutils).

## Implementation Risks
-   **Priority**: Incorrectly setting thread priority can starve the UI thread (if too high) or cause ANRs (if too low).
-   **Zygote Protocol**: The `start` method constructs a strict argument list for the Zygote socket. Any deviation breaks app launching.
