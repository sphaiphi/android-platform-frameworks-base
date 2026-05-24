# BinderProxy - Reverse Engineering Documentation

## Executive Summary
`BinderProxy` is the Java-side representation of a remote `IBinder` object. When a `Binder` is sent across processes, the receiver gets a `BinderProxy`. It acts as a handle to the native `BpBinder` (C++) object, forwarding `transact` calls to the kernel driver.

## Architecture Overview
-   **Role**: Remote IPC Proxy / Handle.
-   **Native Peer**: `BpBinder` (C++). The `mNativeData` field holds the pointer.
-   **Lifecycle Management**: Uses a custom `ProxyMap` (weak-reference cache) to ensure only one Java `BinderProxy` instance exists for a given native `IBinder` handle/address.

## Detailed Functionality

### Proxy Mapping (`ProxyMap`)
-   Maps `long` (native pointer) -> `WeakReference<BinderProxy>`.
-   Ensures object identity: receiving the same Binder twice results in the same `BinderProxy` object (== equality).
-   Handles Garbage Collection: When the Java wrapper dies, the native `BpBinder` refcount is decremented.

### Transaction (`transact`)
-   **Tracing**: Logs `outgoing` transactions.
-   **Listeners**: `ProxyTransactListener` allows intercepting outgoing calls (e.g., for work source propagation).
-   **Native Call**: Invokes `transactNative`, which calls `BpBinder::transact` in C++.

### Death Recipients
-   **`linkToDeath`**: Registers a callback to be notified when the remote process dies.
-   **Implementation**: Maintains a list of `DeathRecipient`s in Java and registers a JNI-level recipient that delegates back to Java.

## Java-to-C++ Translation Guide
-   **Native Equivalent**: `android::BpBinder`.
-   **Serialization**: Written to Parcel as a flat binder object (type, handle, cookie).
-   **Frozen State**: Supports `addFrozenStateChangeCallback` to detect when the remote process is frozen (cached).

## Implementation Risks
-   **Proxy Leak**: `ProxyMap` can grow indefinitely if proxies are leaked. The class includes logic (`CRASH_AT_SIZE`) to crash the process if the map grows too large (25k entries), preventing global stable ref exhaustion in the kernel.
