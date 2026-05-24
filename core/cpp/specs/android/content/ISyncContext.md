# ISyncContext - Reverse Engineering Documentation

## Executive Summary
`ISyncContext` is an AIDL interface passed to `ISyncAdapter.startSync`. It allows the SyncAdapter to report progress ("heartbeat") and completion to the SyncManager.

## Architecture Overview
- **Type:** AIDL Interface.
- **Caller:** SyncAdapter.
- **Implementer:** SyncManager (System).

## API Reference
- `void sendHeartbeat()`
- `void onFinished(SyncResult result)`

## Java-to-C++ Translation Guide
- **AIDL**: C++ generated code.

## Implementation Risks
- None.
