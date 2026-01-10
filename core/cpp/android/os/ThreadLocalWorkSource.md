# ThreadLocalWorkSource - Reverse Engineering Documentation

## Executive Summary
`ThreadLocalWorkSource` tracks the `WorkSource` UID responsible for the code currently executing on the current thread. It allows implicit propagation of work attribution through system service calls without passing `WorkSource` arguments explicitly in every method signature.

## Architecture Overview
-   **Mechanism**: `ThreadLocal<int[]>`. Stores a single UID.
-   **Integration**:
    -   **Binder**: `Binder.execTransact` sets this based on the calling UID of the incoming transaction.
    -   **PowerManager**: Checks `ThreadLocalWorkSource.getUid()` to blame wake locks.

## Detailed Functionality
-   **`setUid(int uid)`**: Sets the current thread's blame UID. Returns a token to restore later.
-   **`restore(long token)`**: Restores previous state.
-   **`getUid()`**: Returns the current value.

## Java-to-C++ Translation Guide
-   **C++ Equivalent**: `android::IPCThreadState` maintains calling identity, but `ThreadLocalWorkSource` is a higher-level concept often used *on top* of raw IPC identity (e.g. when a service explicitly impersonates another UID).
-   **Implementation**: Use `thread_local` storage in C++.

## Implementation Risks
-   **Leaks**: Failing to `restore()` pushes incorrect attribution to subsequent operations on the thread (thread pool pollution).
