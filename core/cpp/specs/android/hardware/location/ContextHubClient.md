# ContextHubClient - Reverse Engineering Documentation

## Executive Summary
`ContextHubClient` is the client-side API for interacting with a specific Context Hub. It allows sending messages to nanoapps, receiving messages (via a callback), and managing the connection lifecycle. It wraps an `IContextHubClient` Binder proxy.

## Architecture Overview
- **Pattern**: Proxy / Facade.
- **Role**: Application-facing API for Context Hub interaction.
- **Resource Management**: Implements `Closeable` and uses `CloseGuard` to ensure connections are closed.

## Detailed Functionality

### Connection Management
- **Creation**: Instantiated by `ContextHubManager`.
- **Proxy**: Holds `IContextHubClient mClientProxy`.
- **ID**: Caches the client ID from the service (`mId`).
- **Closing**: `close()` method cleanly tears down the connection at the service side.

### Messaging
- **Send**: `sendMessageToNanoApp(NanoAppMessage)` forwards to the proxy.
- **Reliable Send**: `sendReliableMessageToNanoApp` creates a `ContextHubTransaction` and uses a callback to wait for acknowledgment.

### Callbacks
- Exposes `callbackFinished()` and `reliableMessageCallbackFinished()` to notify the service when the client has processed a callback (flow control).

## Data Model
- `mAttachedHub`: `ContextHubInfo` (Target hub).
- `mClientProxy`: `IContextHubClient` (Binder interface).
- `mId`: `Integer` (Client ID).

## Java-to-C++ Translation Guide
### Architecture Mapping
- **C++ Class**: `ContextHubClient` class wrapping `sp<IContextHubClient>`.
- **Memory Safety**: Use `sp<IContextHubClient>` (strong pointer) for the proxy.
- **Transactions**: The reliable message transaction logic (creating a transaction object, setting a callback) needs to be replicated if the C++ API requires synchronous-like behavior or future-based async.

### API Contracts
- `sendMessageToNanoApp` returns `int` (result code).
- `close` must be idempotent.

## Questions for C++ Team
- Does the C++ client need to support the "Persistent" mode (PendingIntent-based)? (Likely not, as that's an Android Framework concept).
