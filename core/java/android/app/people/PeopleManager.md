# PeopleManager - Reverse Engineering Documentation

## Executive Summary
`PeopleManager` is the client-side system service wrapper for the `people` service. It provides APIs to publish conversation statuses, query conversation metadata, and register listeners for conversation updates. It handles the Binder IPC details and provides a clean Java API.

## Architecture Overview
- **Pattern**: Proxy / Manager.
- **Components**:
  - `PeopleManager`: Public API surface.
  - `IPeopleManager`: AIDL interface definition for the system service.
  - `ConversationListener`: Callback interface for clients.
  - `ConversationListenerProxy`: Stub implementation to receive Binder callbacks and dispatch them to the client's Executor.

## Detailed Functionality

### Service Connection
- **Constructor**: Fetches `IPeopleManager` via `ServiceManager.getService(Context.PEOPLE_SERVICE)`.
- **Dependency**: Requires the system service to be running.

### Status Management (`addOrUpdateStatus`, `clearStatus`, `clearStatuses`)
**Purpose**: Manage transient statuses (e.g., "in a meeting") for a specific conversation.
**Logic**: Delegates directly to `mService`.
**Validation**: Checks for non-null/non-empty strings.
**Exceptions**: Rethrows `RemoteException` as `RuntimeException`.

### Conversation Queries (`isConversation`, `getStatuses`)
**Purpose**: Retrieve state from the system server.
**Permissions**: `isConversation` requires `android.permission.READ_PEOPLE_DATA`.

### Listener Registration (`registerConversationListener`)
**Purpose**: Observe changes to a specific conversation.
**Logic**:
1. Wraps the client's `ConversationListener` and `Executor` in a `ConversationListenerProxy`.
2. Stores the proxy in `mConversationListeners` map to allow unregistration.
3. Calls `mService.registerConversationListener` with the proxy.
**Thread Safety**: Synchronizes on `mConversationListeners` to manage the listener map.

### Callback Handling (`ConversationListenerProxy`)
**Purpose**: Bridge Binder thread callbacks to the client's specified Executor.
**Inheritance**: Extends `IConversationListener.Stub`.
**Logic**: inside `onConversationUpdate`, executes the client's callback on `mExecutor`. Handles the case where the Binder might be dead or listener null.

## Data Model
- **`mConversationListeners`**: `Map<ConversationListener, Pair<Executor, IConversationListener>>`. Maps the user-provided listener to the generated Binder stub. Used for unregistration lookup.

## API Reference

### `void addOrUpdateStatus(String conversationId, ConversationStatus status)`
Publishes a status. `conversationId` is the shortcut ID.

### `void clearStatus(String conversationId, String statusId)`
Removes a specific status.

### `void registerConversationListener(...)`
Registers a listener. Note that the listener receives updates only for the *specific* conversation identified by package, user, and shortcut ID.

## Java-to-C++ Translation Guide

### Binder Proxy
- Use `android::sp<IPeopleManager>` to hold the service interface.
- Use `android::os::ServiceManager::getService` to obtain the binder.

### Listener Implementation (BnConversationListener)
- C++ needs to implement a native Binder stub for `IConversationListener`.
- **Threading**: The Java implementation allows specifying an `Executor`. In C++, callbacks usually arrive on the Binder thread pool. If the C++ client needs callbacks on a specific thread (e.g., Looper), a similar proxy/trampoline mechanism is needed.

### Map Management
- Use `std::map` or `std::unordered_map` to store active listeners if unregistration is supported.
- **Locking**: Use `std::mutex` to protect the listener map, matching the `synchronized` block in Java.

### Exception Handling
- Java rethrows `RemoteException` as RuntimeException.
- C++ Binder calls return `android::binder::Status`. Check `status.isOk()` and handle errors appropriate (log, return error code, or throw exception if project style permits).

## Implementation Risks
- **Object Lifetime**: In Java, the Proxy holds a reference to the Listener. In C++, care must be taken to avoid cycles or use-after-free if the listener is destroyed while the service still holds a reference to the proxy.
- **Binder Death**: The Java code checks `mListener == null`. C++ should implement `IBinder::DeathRecipient` to clean up if the remote service dies.

## Questions for C++ Team
- Is there a generated C++ header for `IPeopleManager.aidl`? (Likely yes, via AIDL compiler).
