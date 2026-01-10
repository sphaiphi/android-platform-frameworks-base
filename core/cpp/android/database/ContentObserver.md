# ContentObserver - Reverse Engineering Documentation

## Executive Summary
`ContentObserver` is the callback interface for receiving content change notifications. It supports dispatching these notifications to a specific thread via a `Handler` or `Executor`. It also handles the Binder IPC transport (`IContentObserver`) to receive notifications from remote processes.

## Architecture Overview
*   **Components**:
    *   `Handler` / `Executor`: For dispatching `onChange`.
    *   `Transport` (Inner Class): `IContentObserver.Stub` implementation for Binder.

## Detailed Functionality

### Notification Dispatch
*   `dispatchChange(selfChange, uri, flags)`:
    *   If `Executor` exists, execute `onChange` there.
    *   Else if `Handler` exists, `post` `onChange` there.
    *   Else, call `onChange` immediately (current thread).

### IPC Support
*   `getContentObserver()`: Returns the `Transport` binder object. Used to register this observer with a remote `ContentService`.
*   `releaseContentObserver()`: Cleans up the transport.

## Java-to-C++ Translation Guide
*   **Transport**: Needs a C++ `BnContentObserver` implementation.
*   **Threading**: Needs a mechanism to dispatch to a specific `Looper` or `TaskRunner` equivalent in C++.

## Data Model
*   `mHandler`: Legacy Android Handler.
*   `mExecutor`: Java Executor.
*   `mTransport`: Binder stub.
