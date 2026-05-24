# StrictMode - Reverse Engineering Documentation

## Executive Summary
`StrictMode` is a developer tool and policy enforcement mechanism that detects accidental disk or network access on the main thread, as well as various resource leaks (cursors, closeable objects). It can log violations, flash the screen, or crash the app. It propagates policy across Binder calls.

## Architecture Overview
-   **Role**: Policy Enforcer / watchdog.
-   **Policies**:
    -   **ThreadPolicy**: Constraints for the current thread (Disk R/W, Network, Custom Slow Calls).
    -   **VmPolicy**: Constraints for the process (Leaks, File URI exposure, Cleartext Network).
-   **Propagation**:
    -   **Thread Local**: Stores policy in `ThreadLocal` (via `BlockGuard` in Dalvik/libcore).
    -   **Binder**: Transmits the policy mask in the Parcel header (`nativeSetThreadStrictModePolicy`) so the remote side enforces the caller's policy.

## Detailed Functionality

### Detection
-   **Instrumentation**: `BlockGuard` hooks into low-level I/O (`FileInputStream`, `Socket`). `StrictMode` installs a `AndroidBlockGuardPolicy` to handle these callbacks.
-   **Explicit Checks**: `noteDiskRead()`, `noteDiskWrite()` are called manually in framework code.
-   **Binder**: When `Binder.onTransact` runs, it clears strict mode violations but restores the caller's policy if needed.

### Penalties
-   **Log**: Write to Logcat.
-   **Dropbox**: Write stack trace to DropBoxManager.
-   **Dialog**: Show an "ANR-like" dialog.
-   **Death**: Crash the process.
-   **Flash**: Flash the screen red (requires `IWindowManager`).

## Data Model
-   **Bitmasks**: `DETECT_THREAD_*`, `PENALTY_*`.
-   **ViolationInfo**: `Parcelable` class that captures the stack trace, policy mask, and violation details to send back to the caller (if `PENALTY_GATHER` is set).

## Java-to-C++ Translation Guide
-   **Binder Integration**: `IPCThreadState` in C++ has `getStrictModePolicy()` and `setStrictModePolicy()`.
-   **BlockGuard**: C++ code using `libcore` abstractions (rare in native services) might use this, but typically C++ services don't enforce StrictMode on themselves unless processing a Binder transaction on behalf of Java.
-   **Parcel**: The `Parcel` C++ class handles reading/writing the StrictMode policy header.

## Implementation Risks
-   **Performance**: Stack trace generation is slow. StrictMode logic attempts to sample or throttle logging.
-   **False Positives**: Valid disk I/O on main thread during startup is common.
