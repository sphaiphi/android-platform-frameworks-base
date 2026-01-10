# ContentResolver - Reverse Engineering Documentation

## Executive Summary
`ContentResolver` is the primary interface for applications to interact with the Android content model. It acts as a client-side proxy that discovers and communicates with `ContentProvider` instances, both within the same process and across process boundaries using Binder IPC.

## Architecture Overview
- **Inheritance:** `Object`.
- **Core Pattern:** Service Locator / Proxy.
- **Dependencies:** `IContentService` (System Sync Manager), `Context`, `IContentProvider`.

## Detailed Functionality

### Provider Discovery and Lifecycle
- **`acquireProvider(Uri)`**: Resolves a URI to a provider. It contacts the `ActivityManagerService` to find or start the process owning the provider.
- **Stable vs Unstable**: 
    - **Stable**: Keeps the target process alive. If the provider process dies, the client process is typically killed to ensure consistency.
    - **Unstable**: Allows the provider process to die without killing the client. Used for discovery and non-critical operations.
- **`ContentProviderClient`**: A wrapper that holds a reference to a provider, allowing multiple calls without repeated resolution.

### Data Operations (CRUD)
- **`query`**: Returns a `Cursor`. Supports standard SQL-like arguments and the newer `Bundle` based query arguments (allowing pagination and custom extensions).
- **`insert`, `update`, `delete`**: Standard modification APIs.
- **`bulkInsert`**: Optimized for multiple inserts.
- **`applyBatch`**: Executes a list of `ContentProviderOperation` objects atomically or as a transaction.

### File and Stream Access
- **`openInputStream`, `openOutputStream`**: Accesses data as streams.
- **`openAssetFileDescriptor`, `openTypedAssetFileDescriptor`**: Accesses raw files or sub-sections of files (e.g., for large blobs).

### Content Observers
- **`registerContentObserver(Uri, boolean, ContentObserver)`**: Allows apps to listen for data changes.
- **`notifyChange(Uri, ContentObserver, ...)`**: Providers call this to broadcast that data has changed. Uses Binder callbacks.

### Sync Framework Integration
- **`requestSync`, `cancelSync`**: Interfaces with `SyncManager`.
- **`setIsSyncable`, `getIsSyncable`**: Manages whether a provider/account pair is eligible for syncing.
- **`addPeriodicSync`, `removePeriodicSync`**: Schedules recurring background syncs.

## Data Model
- `mContext`: The associated `Context`.
- `mPackageName`: The calling package name (for attribution).
- `mAttributionTag`: For permission auditing.

## API Reference
- `public final Cursor query(Uri uri, ...)`
- `public final Uri insert(Uri url, ContentValues values)`
- `public final ContentProviderClient acquireContentProviderClient(Uri uri)`
- `public static void requestSync(Account account, String authority, Bundle extras)`

## Java-to-C++ Translation Guide
- **Binder IPC**: All calls eventually delegate to `IContentProvider` (Binder proxy).
- **Cursor**: Requires a C++ implementation of `Cursor` (usually `SqliteCursor` or a Binder-parcelable `CursorWindow`).
- **Permissions**: Must pass `AttributionSource` for modern Android safety auditing.

## Implementation Risks
- **Deadlocks**: Synchronous `acquireProvider` calls can block the main thread.
- **Resource Leaks**: `ContentProviderClient` must be released via `close()`.
- **Process Death**: Handling `DeadObjectException` when the provider process crashes.
