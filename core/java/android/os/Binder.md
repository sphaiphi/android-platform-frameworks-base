# Binder - Reverse Engineering Documentation

## Executive Summary
`Binder` is the core class of Android's IPC (Inter-Process Communication) mechanism. It implements the `IBinder` interface and represents a local object that can be sent to other processes. When sent, it arrives as a `BinderProxy`. It handles the dispatching of transactions (`onTransact`) sent from remote clients.

## Architecture Overview
-   **Role**: Local IPC Endpoint / Stub.
-   **Native Peer**: `JavaBBinder` (C++). Holds a pointer `mObject` to the native object.
-   **Interface**: Implements `IBinder`.
-   **Transaction Loop**: The `execTransact` method is the entry point called from native code (`android_util_Binder.cpp`) when a transaction arrives.

## Detailed Functionality

### Transaction Dispatch (`execTransact`)
1.  **Context Setup**: Sets `ThreadLocalWorkSource` based on the calling UID (if not an RPC transaction).
2.  **Tracing**: Starts systrace sections (`AIDL::java::ClassName::MethodName`).
3.  **Observer**: Notifies `BinderInternal.Observer` (if set) for call tracking.
4.  **AppOps**: Handles `FLAG_COLLECT_NOTED_APP_OPS` to track permission usage.
5.  **`onTransact`**: Calls the overridable method where specific AIDL interfaces implement their stub logic (switch-case on transaction code).
6.  **Cleanup**: Recycles Parcels, restores Calling Identity/WorkSource.

### Identity Management
-   **`getCallingUid()` / `getCallingPid()`**: Native calls to retrieve the caller's identity from the kernel driver.
-   **`clearCallingIdentity()` / `restoreCallingIdentity()`**: Manages the thread-local IPC state (often a 64-bit token packing UID and PID).

### Extension Mechanism
-   **`setExtension` / `getExtension`**: Allows attaching an additional binder interface to an existing one, facilitating versioning and extensibility without breaking the primary interface.

## Java-to-C++ Translation Guide
-   **Native Equivalent**: `android::BBinder`.
-   **JNI Bridge**: `android_util_Binder.cpp` links this Java class to `libbinder`.
-   **Object Lifecycle**: `Binder` uses `NativeAllocationRegistry` to manage the lifetime of the native `JavaBBinderHolder`.

## Implementation Risks
-   **Blocking**: `onTransact` runs on a binder thread. Blocking here stalls the thread pool. `setWarnOnBlocking` helps detect this.
-   **Exception Handling**: RuntimeExceptions in `onTransact` are caught and written to the reply Parcel as exceptions, unless it's a oneway call (where they are logged and swallowed).
