# ScreenRecordingCallbacks - Reverse Engineering Documentation

## Executive Summary
`ScreenRecordingCallbacks` is a singleton manager that allows applications to detect when their content is being captured by a screen recorder or mirror. It registers a global listener with the `WindowManagerService` and dispatches state changes (`VISIBLE` vs. `NOT_VISIBLE`) to app-registered consumers.

## Architecture Overview
*   **Role**: Privacy awareness monitor.
*   **IPC**: Registers an `IScreenRecordingCallback` with the `WindowManagerService`.
*   **Threading**: Callbacks are executed on a user-provided `Executor` after clearing the calling identity (Binder security).

## Detailed Functionality
*   **`addCallback()`**: Registers a new listener. If it's the first listener, it establishes the binder connection to the system server.
*   **`removeCallback()`**: Unregisters a listener. When the last one is removed, it detaches the binder connection to save resources.

## Java-to-C++ Translation Guide
*   **Service Link**: Communicates with `IWindowManager`.
*   **Callback**: Implement the `BnScreenRecordingCallback` AIDL interface.

## Implementation Risks
*   **Permission**: This functionality is guarded by the `DETECT_SCREEN_RECORDING` permission.
*   **Latency**: There may be a brief delay between the start of recording and the application receiving the callback.
