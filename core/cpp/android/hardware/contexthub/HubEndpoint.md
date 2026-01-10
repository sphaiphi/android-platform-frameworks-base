# HubEndpoint - Reverse Engineering Documentation

## Executive Summary
`HubEndpoint` represents a local endpoint exposed to the Context Hub and Vendor Hub ecosystem. It encapsulates the lifecycle management, session handling, and message transmission for an endpoint. It acts as the bridge between the application/service logic and the underlying `IContextHubService`.

## Architecture Overview
- **Type**: Lifecycle & Session Manager.
- **Package**: `android.hardware.contexthub`.
- **Communication**: Uses `IContextHubEndpoint` (Binder) to talk to the system service.
- **Callbacks**: Dispatches events to `HubEndpointLifecycleCallback` and `HubEndpointMessageCallback`.
- **Concurrency**: Uses `Executor`s for callback dispatch and internal locking (`mLock`) for session state management.

## Detailed Functionality

### Lifecycle Management
- **Registration**: `register(IContextHubService)` binds this endpoint to the system service.
- **Unregistration**: `unregister()` disconnects from the service and closes all active sessions.

### Session Management
- **Opening Sessions**: `openSession` initiates a connection to a destination endpoint.
- **Accepting/Rejecting Sessions**: Handles incoming session requests via `mServiceCallback.onSessionOpenRequest`.
- **Closing Sessions**: `closeSession` terminates a session.
- **Active Sessions**: Maintains a `SparseArray<HubEndpointSession>` of active sessions.

### Messaging
- **Sending**: `sendMessage` transmits data through the Binder interface.
- **Receiving**: `onMessageReceived` callback handles incoming data, dispatching it to the registered `HubEndpointMessageCallback`.

### Internal State Logic
- **`Reason` IntDef**: Defines closure/failure reasons (e.g., `REASON_ENDPOINT_STOPPED`, `REASON_PERMISSION_DENIED`).
- **Callback Interfaces**:
    - `EndpointConsumer`: Internal functional interface for Binder calls.
    - `IContextHubEndpointCallback`: Stub implementation handling events from the system server.

## Data Model
- `mActiveSessions`: `SparseArray<HubEndpointSession>` - Maps session IDs to session objects.
- `mServiceToken`: `IContextHubEndpoint` - Binder token for the registered endpoint.
- `mPendingHubEndpointInfo`: `HubEndpointInfo` - Configuration before registration.
- `mAssignedHubEndpointInfo`: `HubEndpointInfo` - Configuration assigned by the service (with ID).

## API Reference
- `register`, `unregister`
- `openSession`, `closeSession`
- `getVersion`, `getTag`, `getServiceInfoCollection`
- `Builder`: For constructing instances.

## Java-to-C++ Translation Guide
### Design Pattern
- **Proxy/Facade**: Represents the local side of a remote endpoint.
- **Observer**: For lifecycle and message callbacks.

### C++ Equivalent
```cpp
class HubEndpoint {
public:
    void registerEndpoint(sp<IContextHubService> service);
    void unregisterEndpoint();
    std::shared_ptr<HubEndpointSession> openSession(const HubEndpointInfo& dest, const std::string& serviceDesc);
    // ...
private:
    sp<IContextHubEndpoint> mServiceToken;
    std::map<int, std::shared_ptr<HubEndpointSession>> mActiveSessions;
    // ...
};
```
### Implementation Guidance
- The inner `IContextHubEndpointCallback` stub needs to be implemented as a `BnContextHubEndpointCallback` in C++.
- Thread safety is critical for `mActiveSessions`.

## Implementation Risks
- **Deadlocks**: Careful synchronization is needed when modifying session lists while processing callbacks.
- **RemoteException**: All binder calls must handle potential remote failures.
