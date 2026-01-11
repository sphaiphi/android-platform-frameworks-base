# AmbientContextManager - Reverse Engineering Documentation

## Executive Summary
`AmbientContextManager` is the client-side system service wrapper (Manager) that provides access to the Ambient Context detection features. It acts as a proxy, marshalling client requests and callbacks to the system service (`IAmbientContextManager`). It handles permissions, threading (executors), and IPC callback wrapping.

## Architecture Overview
-   **Type**: System Service Manager.
-   **Design Pattern**: Proxy / Facade.
-   **Relationships**:
    -   Obtained via `Context.getSystemService(Context.AMBIENT_CONTEXT_SERVICE)`.
    -   Holds reference to `IAmbientContextManager` (Binder stub).
    -   Wraps client-provided `Consumer` and `AmbientContextCallback` into `RemoteCallback` or `IAmbientContextObserver`.

## Detailed Functionality

### 1. Status Query (`queryAmbientContextServiceStatus`)
**Purpose**: Checks if specific events are supported and user-consented.
**Algorithm**:
1.  Accepts a set of event types, an executor, and a consumer callback.
2.  Wraps the consumer in a `RemoteCallback`.
3.  Inside `RemoteCallback`:
    -   Extracts status integer from result bundle (`STATUS_RESPONSE_BUNDLE_KEY`).
    -   Clears calling identity.
    -   Executes client consumer on the provided executor.
    -   Restores calling identity.
4.  Calls `mService.queryServiceStatus` with event types array and package name.
**C++ Guidance**:
-   Requires Binder callback implementation.
-   Requires conversion of Set/Vector to array for IPC.

### 2. Registration (`registerObserver`)
**Purpose**: Starts detection for requested events.
**Variants**:
1.  **PendingIntent-based**:
    -   Accepts `AmbientContextEventRequest`, `PendingIntent`, `Executor`, `Consumer<Status>`.
    -   Validates PendingIntent is mutable.
    -   Wraps status consumer in `RemoteCallback`.
    -   Calls `mService.registerObserver`.
2.  **Callback-based**:
    -   Accepts `AmbientContextEventRequest`, `Executor`, `AmbientContextCallback`.
    -   Creates a local stub `IAmbientContextObserver.Stub`.
    -   **Stub Implementation**:
        -   `onEvents`: Clears identity, executes `callback.onEvents` on executor.
        -   `onRegistrationComplete`: Clears identity, executes `callback.onRegistrationComplete` on executor.
    -   Calls `mService.registerObserverWithCallback`.

### 3. Unregistration (`unregisterObserver`)
**Purpose**: Stops detection.
**Algorithm**:
1.  Calls `mService.unregisterObserver` with the calling package name.

### 4. Consent UI (`startConsentActivity`)
**Purpose**: Launches system UI for user consent.
**Algorithm**:
1.  Calls `mService.startConsentActivity` with event types and package name.

## Data Model (Internal)
-   **Status Codes**: `STATUS_UNKNOWN` (0) to `STATUS_ACCESS_DENIED` (5).
-   **Bundle Keys**: `STATUS_RESPONSE_BUNDLE_KEY`, `EXTRA_AMBIENT_CONTEXT_EVENTS`.

## API Reference
Refer to `AmbientContextManager.java` for full method signatures. Key public methods:
-   `queryAmbientContextServiceStatus`
-   `startConsentActivity`
-   `registerObserver` (2 overloads)
-   `unregisterObserver`
-   `getEventsFromIntent` (Helper for PendingIntent flows)

## Java-to-C++ Translation Guide

### IPC / Binder
-   Java `IAmbientContextManager` -> C++ `IAmbientContextManager` (generated from AIDL).
-   Java `IAmbientContextObserver.Stub` -> C++ `BnAmbientContextObserver`.
-   Java `RemoteCallback` -> C++ `android::os::IRemoteCallback` (or equivalent usage).

### Threading & Identity
-   Java: `Binder.clearCallingIdentity()` / `restoreCallingIdentity()` prevents privilege escalation or confusion during callback execution.
-   **C++ Implication**: When receiving callbacks from the service in the C++ layer, if dispatching to a different thread or context, verify if identity clearing is relevant (usually less critical in native standalone clients unless simulating app behavior).

### Arrays vs Sets
-   The Manager converts `Set<Integer>` to `int[]` for the AIDL interface. C++ should send `std::vector<int32_t>`.

## Test Cases & Validation
-   **Permission Check**: Methods require `ACCESS_AMBIENT_CONTEXT_EVENT`. Verify security exception behavior.
-   **Callback Execution**: Verify callbacks run on the specified thread/executor logic (in C++: specific `Looper` or thread pool).
-   **Argument Validation**: Pass mutable vs immutable PendingIntent (Java side check).

## Implementation Risks
-   **Binder Object Lifetime**: When registering a callback (`IAmbientContextObserver`), the client (Manager) must ensure the stub object remains alive as long as the service needs it. In Java, this is implicit. In C++, use `sp<IBinder>` carefully.

## Questions for C++ Team
-   Will the C++ client rely on `PendingIntent` flows? (Usually specific to Android App layer). If not, the `PendingIntent` variant of `registerObserver` might be skippable.
-   Is `RemoteCallback` infrastructure available in the target C++ utils?
