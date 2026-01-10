# BackupManager - Reverse Engineering Documentation

## Executive Summary
`BackupManager` is the public API surface for applications to interact with the Android Backup Service. It allows apps to trigger backups, request restores (deprecated), and manage transport configurations. It communicates with the system service `BackupManagerService` via Binder.

## Architecture Overview
-   **Role**: Client API.
-   **IPC**: Uses `IBackupManager` (Binder) to talk to the system server.
-   **Permissions**: Many methods require `android.permission.BACKUP` or system privileges.

## Detailed Functionality

### Core Operations
-   **`dataChanged()`**: Signals that data has changed and a backup is needed. Triggers a scheduled backup.
-   **`requestBackup()`**: Triggers an immediate backup for specific packages (requires permission).
-   **`backupNow()`**: Force run of pending key/value backups.

### Transport Management (System/Privileged)
-   `listAllTransports()`: Enumerates transports.
-   `selectBackupTransport()`: Changes the active transport.
-   `updateTransportAttributes()`: Updates UI labels/intents for transports.
-   `getCurrentTransport()`: Gets active transport name.

### Restore
-   **`beginRestoreSession()`**: Opens a `RestoreSession` to query sets and perform restores.
-   **`requestRestore()`**: Deprecated no-op in modern Android.

### Service Management
-   `setBackupEnabled()`: Toggles global backup state.
-   `isBackupEnabled()`: Checks state.

### Monitoring
-   `getBackupRestoreEventLogger()`: Helper to get a logger for an agent.

## Data Model
-   **Constants**: Error codes (`SUCCESS`, `ERROR_BACKUP_NOT_ALLOWED`, etc.), Flags (`FLAG_NON_INCREMENTAL_BACKUP`).
-   **Service Reference**: `sService` (cached `IBackupManager`).

## Java-to-C++ Translation Guide
-   **Service Manager**: In C++, use `defaultServiceManager()->getService(String16("backup"))` to get the binder.
-   **Wrappers**: Java uses wrappers (`BackupObserverWrapper`) to dispatch binder callbacks to the main thread. C++ implementation depends on the threading model (e.g., if callbacks need to run on a specific Looper).

## Implementation Risks
-   **Binder Stability**: Handling `RemoteException` (dead object) is handled in Java by catching and logging. C++ clients should monitor `linkToDeath`.
