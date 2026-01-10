# SearchSession - Reverse Engineering Documentation

## Executive Summary
`SearchSession` is the client-side controller for a search interaction. It manages the connection to the system search service (`ISearchUiManager`), handles session identity, and proxies queries and events.

## Architecture Overview
-   **Package**: `android.app.search`
-   **Type**: Class, implements `AutoCloseable`
-   **Dependencies**:
    -   `ISearchUiManager` (AIDL interface)
    -   `ISearchCallback` (AIDL interface)
    -   `SearchSessionId`
    -   `SearchContext`

## Detailed Functionality

### Lifecycle
1.  **Initialization (`SearchSession` constructor)**:
    -   Obtains `ISearchUiManager` binder from `ServiceManager` (`Context.SEARCH_UI_SERVICE`).
    -   Generates a `SearchSessionId`: `packageName + ":" + UUID`.
    -   Injects `packageName` into `SearchContext`.
    -   Calls `mInterface.createSearchSession(context, sessionId, token)`.
    -   Initializes `CloseGuard`.
2.  **Destruction (`destroy` / `close`)**:
    -   Guards against double-close using `AtomicBoolean mIsClosed`.
    -   Calls `mInterface.destroySearchSession(sessionId)`.
    -   Closes `CloseGuard`.

### Core Operations
1.  **Query (`query`)**:
    -   Checks if closed.
    -   Wraps the provided `Consumer<List<SearchTarget>>` and `Executor` into a `CallbackWrapper` (extends `ISearchCallback.Stub`).
    -   Calls `mInterface.query(sessionId, input, callbackWrapper)`.
2.  **Event Notification (`notifyEvent`)**:
    -   Checks if closed.
    -   Calls `mInterface.notifyEvent(sessionId, query, event)`.
3.  **Zero-State Updates (`registerEmptyQueryResultUpdateCallback`)**:
    -   Manages a map `mRegisteredCallbacks` to associate user callbacks with Binder stubs.
    -   Prevent duplicate registration.
    -   Calls `mInterface.registerEmptyQueryResultUpdateCallback`.

### Callback Management
-   **CallbackWrapper**:
    -   Extends `ISearchCallback.Stub`.
    -   Handles `onResult(ParceledListSlice result)`.
    -   Deserializes the list.
    -   **Debug/Instrumentation**: Injects `key_ipc_start` timestamp into the extras of the first item if present (for latency tracking).
    -   Executes the user callback on the provided Executor.
    -   Manages Binder identity (`clearCallingIdentity`/`restoreCallingIdentity`).

## Java-to-C++ Translation Guide

### Binder Interfaces
-   **ISearchUiManager**:
    -   `createSearchSession(SearchContext, SearchSessionId, IBinder)`
    -   `query(SearchSessionId, Query, ISearchCallback)`
    -   `notifyEvent(SearchSessionId, Query, SearchTargetEvent)`
    -   `registerEmptyQueryResultUpdateCallback(SearchSessionId, ISearchCallback)`
    -   `unregisterEmptyQueryResultUpdateCallback(SearchSessionId, ISearchCallback)`
    -   `destroySearchSession(SearchSessionId)`
-   **ISearchCallback**:
    -   `onResult(ParceledListSlice result)`

### C++ Implementation Notes
-   **Session ID Generation**: C++ needs a UUID generator to match the format.
-   **Binder Token**: `mToken = new Binder()` in Java creates a local binder token for identity. C++ should create a `BBinder` or equivalent to pass as the token.
-   **Thread Safety**: Access to `mRegisteredCallbacks` is synchronized. `mIsClosed` is atomic.
-   **ParceledListSlice**: This is a specific Android container for large lists across IPC. C++ needs a compatible reader/writer.

## Implementation Risks
-   **ParceledListSlice**: Handling this correctly in C++ is non-trivial if a utility class doesn't already exist in the NDK/Frameworks utils.
-   **CloseGuard**: Standard Java mechanism for resource leak detection. C++ destructors (RAII) naturally handle this, so explicit CloseGuard logic might not be needed, but the `destroySearchSession` IPC call must happen in the destructor.

## Questions for C++ Team
-   Is `ParceledListSlice` available in the C++ binder utilities?
