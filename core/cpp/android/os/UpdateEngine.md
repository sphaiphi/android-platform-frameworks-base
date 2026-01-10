# UpdateEngine - Reverse Engineering Documentation

## Executive Summary
`UpdateEngine` exposes the A/B (Seamless) system update functionality to system apps (like GmsCore). It wraps the `IUpdateEngine` Binder interface (provided by `update_engine` daemon).

## Architecture Overview
-   **Role**: OTA Client.
-   **Service**: `android.os.IUpdateEngine`.
-   **Daemon**: `update_engine` (C++ native daemon).

## Detailed Functionality
-   **`applyPayload(...)`**: Starts an update. Takes a URL or FD, offset, size, and metadata properties (key-value pairs).
-   **`bind(UpdateEngineCallback)`**: Registers a listener for status updates (downloading, verifying, finalising) and completion codes.
-   **`suspend` / `resume` / `cancel`**: Flow control.

## Data Model
-   **Status**: `IDLE`, `DOWNLOADING`, `VERIFYING`, `FINALIZING`, `UPDATED_NEED_REBOOT`.
-   **Error Codes**: `SUCCESS`, `ERROR`, `FILESYSTEM_COPIER_ERROR`, etc.

## Java-to-C++ Translation Guide
-   **Binder**: `android::os::IUpdateEngine` (AIDL generated).
-   **Daemon**: The daemon itself is C++. This class is just the Java client. A C++ client would likely talk to the daemon directly or via the same Binder interface.

## Implementation Risks
-   **Permissions**: Strictly controlled (`UPDATE_ENGINE_SERVICE` requires privileged permissions).
-   **Blocking**: Payload application happens in the background daemon.
