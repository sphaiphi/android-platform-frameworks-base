# SyncContext - Reverse Engineering Documentation

## Executive Summary
`SyncContext` is a wrapper around the `ISyncContext` binder interface. It provides convenience methods for the SyncAdapter to report progress (`onFinished`) and heartbeat status.

## Architecture Overview
- **Relationship:** Passed to `AbstractThreadedSyncAdapter.onPerformSync`. Wraps `ISyncContext`.

## Detailed Functionality
- **`updateHeartbeat()`**: Sends a heartbeat to the `SyncManager` if enough time (1s) has passed since the last one.
- **`onFinished(SyncResult)`**: Reports completion.

## Data Model
- `mSyncContext`: `ISyncContext` (Binder proxy).
- `mLastHeartbeatSendTime`: `long`.

## API Reference
- `public void onFinished(SyncResult result)`

## Java-to-C++ Translation Guide
- **Binder**: Wraps the `ISyncContext` proxy.

## Implementation Risks
- **Throttling**: The heartbeat throttling logic prevents flooding the system process with IPC calls.