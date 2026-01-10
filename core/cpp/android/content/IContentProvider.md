# IContentProvider - Reverse Engineering Documentation

## Executive Summary
`IContentProvider` is the core hand-written Binder interface used for Inter-Process Communication (IPC) with `ContentProvider`s. Unlike standard AIDL-generated interfaces, it defines its transaction codes manually and provides both synchronous and asynchronous versions of key methods like `getType`.

## Architecture Overview
- **Type:** Interface (extending `IInterface`).
- **Implementer:** `ContentProviderNative` (Stub), `ContentProviderProxy` (Proxy).
- **Usage:** Low-level IPC protocol used by `ContentResolver` and `ContentProviderClient`.

## Detailed Functionality

### Core Data Methods
- **`query`**: Executes a query and returns a `Cursor`. Requires an `AttributionSource` for security auditing.
- **`insert`, `bulkInsert`**: Adds new data.
- **`update`, `delete`**: Modifies or removes existing data.
- **`applyBatch`**: Supports atomic execution of multiple operations.

### Type Resolution
- **`getType`**: Synchronous resolution of MIME types.
- **`getTypeAsync`**: Oneway version that returns the result via a `RemoteCallback`. Used to avoid blocking the caller during MIME type discovery.

### File and Asset Access
- **`openFile`, `openAssetFile`, `openTypedAssetFile`**: Returns file descriptors (`ParcelFileDescriptor` or `AssetFileDescriptor`) for reading/writing raw data.

### URI Management
- **`canonicalize`, `uncanonicalize`**: Converts URIs to a persistent, stable format (useful for data that might move).
- **`checkUriPermission`**: Low-level check for fine-grained URI access.

## Data Model (IPC Protocol)
The interface defines manual transaction codes starting from `IBinder.FIRST_CALL_TRANSACTION`:
- `QUERY_TRANSACTION` (1)
- `GET_TYPE_TRANSACTION` (2)
- `INSERT_TRANSACTION` (3)
- ...
- `GET_TYPE_ASYNC_TRANSACTION` (28)

## API Reference
- `Cursor query(AttributionSource attributionSource, Uri url, ...)`
- `void getTypeAsync(AttributionSource attributionSource, Uri url, RemoteCallback callback)`
- `AssetFileDescriptor openAssetFile(...)`

## Java-to-C++ Translation Guide
- **Manual Binder**: In C++, this corresponds to a class inheriting from `BBinder` (on the provider side) and `BpInterface` (on the client side). The `onTransact` and `remote()->transact` calls must use the exact same integer constants defined in the Java interface.
- **AttributionSource**: Crucial for cross-process permission tracking. Must be correctly parceled and unparceled.

## Implementation Risks
- **Protocol Sync**: Because the transaction codes are manual, any addition or reordering must be perfectly synchronized between the Java and C++ implementations.
- **Blocking Calls**: While some methods are async, most are synchronous. C++ clients should be careful not to block the UI thread on Binder calls.
