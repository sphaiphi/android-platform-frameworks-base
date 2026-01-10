# ISyncAdapter - Reverse Engineering Documentation

## Executive Summary
`ISyncAdapter` is the AIDL interface that SyncAdapters must implement to receive sync requests from the `SyncManager` service.

## Architecture Overview
- **Type:** AIDL Interface (Oneway).
- **Implementer:** `AbstractThreadedSyncAdapter` (via `ISyncAdapterImpl`).

## API Reference
- `void onUnsyncableAccount(ISyncAdapterUnsyncableAccountCallback cb)`
- `void startSync(ISyncContext syncContext, String authority, Account account, Bundle extras)`
- `void cancelSync(ISyncContext syncContext)`

## Java-to-C++ Translation Guide
- **AIDL**: C++ generated code.

## Implementation Risks
- **Thread Safety**: Calls come from Binder thread pool.
