# ContextHubManager - Reverse Engineering Documentation

## Executive Summary
`ContextHubManager` is the system service manager class for Context Hubs. It provides APIs to discover hubs, load/unload nanoapps, create clients (`ContextHubClient`), and manage callbacks. It wraps the `IContextHubService` Binder interface.

## Architecture Overview
- **Pattern**: Manager / System Service Wrapper.
- **Role**: Entry point for applications to access Context Hub features.
- **Dependencies**: `IContextHubService`, `ContextHubClient`, `ContextHubTransaction`.

## Detailed Functionality

### Client Creation
- `createClient(...)`: Registers a client with the service, returning a `ContextHubClient` instance. Supports both callback-based and `PendingIntent`-based clients.

### NanoApp Management (Transactional)
- `loadNanoApp`, `unloadNanoApp`, `enableNanoApp`, `disableNanoApp`, `queryNanoApps`: These return `ContextHubTransaction` objects.
- Uses `ContextHubTransactionHelper` to create callbacks that bridge the async service response to the transaction object.

### Endpoint Discovery (Offload API)
- `findEndpoints`: Discovery of Hub Endpoints.
- `registerEndpointDiscoveryCallback`: Registers callbacks for endpoint lifecycle events.

### Legacy Support
- Contains many deprecated methods (`loadNanoApp(int, NanoApp)`, `registerCallback`, etc.) that map to older HAL versions or earlier API designs.

### Callback Handling
- Manages a local `IContextHubCallback` stub to receive global messages (deprecated path) or client-specific callbacks via the inner `createClientCallback`.

## Data Model
- `mService`: `IContextHubService` (Binder proxy).
- `mDiscoveryCallbacks`: Map of registered discovery callbacks.

## Java-to-C++ Translation Guide
### Architecture Mapping
- **C++ Class**: `ContextHubManager`.
- **Transactions**: Implement the `ContextHubTransaction` pattern to handle async Binder calls cleanly.
- **Service Access**: `defaultServiceManager()->getService("contexthub")`.

### Key Features to Port
- **`createClient`**: The primary way to interact.
- **`queryNanoApps`**: Essential for state recovery.
- **`load/unload`**: Core management.

## Questions for C++ Team
- Should the C++ manager support the legacy APIs, or only the modern `ContextHubClient` + `Transaction` based APIs? (Recommend dropping legacy).
