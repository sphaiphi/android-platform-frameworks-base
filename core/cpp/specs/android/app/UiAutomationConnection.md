# UiAutomationConnection - Reverse Engineering Documentation

## Executive Summary
`UiAutomationConnection` is a highly privileged Binder object that provides the backend implementation for the `UiAutomation` class. It resides in the system server (or a trusted process) and grants access to low-level operations that are typically only available to the shell, such as raw input injection, system rotation overrides, and shell command execution. It acts as a bridge for test instrumentation to perform actions across application boundaries.

## Architecture Overview
- **Inheritance**: Extends `IUiAutomationConnection.Stub`.
- **System Dependencies**: Interfaces with:
    - `IWindowManager`: For rotation and frame statistics.
    - `IAccessibilityManager`: For accessibility service registration.
    - `IPermissionManager`: For runtime permission granting/revocation.
    - `IActivityManager`: For shell permission identity management.
- **Security**: Validates that it is called by a trusted UID (root, system, or the process that originally connected).

## Detailed Functionality

### Connection Lifecycle
**Purpose**: Managing the session with `UiAutomation`.
- `connect(...)`: Registers the caller as a UI test automation service and stores the current device rotation state to allow later restoration.
- `disconnect()`: Unregisters the service and restores the original rotation state.

### Input Simulation
**Purpose**: Injecting events into the system.
- `injectInputEvent(...)`: Uses `InputManagerGlobal` to deliver events. It automatically syncs input transactions with the `WindowManager` to handle animations.
- `setRotation(int rotation)`: Directly calls `mWindowManager.freezeRotation` or `thawRotation`.

### Privileged System Control
- `executeShellCommand(...)`: Spawns a native process and uses a `Repeater` thread to bridge standard input/output/error streams to `ParcelFileDescriptor` objects.
- `grantRuntimePermission(...)` / `revokeRuntimePermission(...)`: Modifies the permission state for specific packages and users.
- `adoptShellPermissionIdentity(...)`: Triggers the `ActivityManager` to delegate shell-level permissions to the caller's UID.

### Screen and Performance Metrics
- `takeScreenshot(...)`: Uses `mWindowManager.captureDisplay` to retrieve the screen buffer.
- `getWindowContentFrameStats(...)`: Fetches rendering timing data for a specific window token.

## API Reference (Internal)
- `public void shutdown()`: Forcibly closes the connection.
- `class Repeater`: Internal thread logic for streaming shell data.

## Java-to-C++ Translation Guide
- **Binder Implementation**: port the `BnUiAutomationConnection` stub to a native C++ service.
- **Process Spawning**: Use `fork` and `exec` for shell command execution, carefully managing pipe redirection for stdout/stderr.
- **Native Services**: Interface with `android::ServiceManager` to retrieve native handles for `window`, `accessibility`, and `activity` services.

## Implementation Risks
- **Shell Injection**: spawing processes via `Runtime.getRuntime().exec(command)` is a security risk. C++ implementation should sanitize inputs and enforce strict UID checks.
- **Thread Leaks**: The `Repeater` threads and cleanup logic must ensure that all file descriptors and child processes are correctly reaped.
- **Rotation State**: Failure to call `restoreRotationStateLocked` can leave the device in a "frozen" rotation state, breaking standard user interaction.
