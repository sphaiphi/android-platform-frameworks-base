# Instrumentation - Reverse Engineering Documentation

## Executive Summary
`Instrumentation` is a base class for implementing application instrumentation code (for testing). It runs before the application code, monitoring system interaction.

## Architecture Overview
*   **Role**: Test Harness / Monitor.
*   **Key Fields**:
    *   `mThread`: `ActivityThread`.
    *   `mInstrContext`: Context of the test apk.
    *   `mAppContext`: Context of the target app.
    *   `mUiAutomation`: UI Automation support.

## Detailed Functionality

### Initialization
*   `onCreate(Bundle)`: Called on startup.
*   `start()`: Starts the instrumentation thread.

### Activity Monitoring
*   `addMonitor`, `checkMonitorHit`, `waitForMonitor`.
*   `ActivityMonitor`: Intercepts activity starts.
*   `execStartActivity`: Hook called by `Activity`/`ContextImpl` to allow instrumentation to monitor/block starts.

### Sync Execution
*   `runOnMainSync`: Runs code on main thread and waits.
*   `startActivitySync`: Starts activity and waits for creation.
*   `sendKeySync`, `sendPointerSync`: Input injection (requires permissions).

### Lifecycle Hooks
*   `callActivityOnCreate`, `callActivityOnResume`, etc. Wraps standard lifecycle calls.

## Java-to-C++ Translation Guide
*   **Testing Framework**: This is core to Android's testing infrastructure.
*   **Hooks**: Requires hooks in `ActivityThread` and `ContextImpl` to function.

## Implementation Risks
*   **Security**: Input injection and process control require privileged access or specific environment (instrumentation mode).
