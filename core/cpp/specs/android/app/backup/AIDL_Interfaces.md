# AIDL Interfaces - Reverse Engineering Documentation

## Executive Summary
Overview of AIDL interfaces for the Backup subsystem.

### IBackupManager.aidl
-   **Role**: System Service Interface.
-   **Methods**:
    -   `dataChanged`: Notify update.
    -   `requestBackup`: Trigger backup.
    -   `selectBackupTransport`: Configure transport.
    -   `beginRestoreSession`: Start restore.
    -   `setBackupEnabled`, `isBackupEnabled`.

### IBackupAgent.aidl
-   **Role**: Application Agent Interface (System calls App).
-   **Methods**:
    -   `doBackup`: KV backup.
    -   `doRestore`: KV restore.
    -   `doFullBackup`: Full backup.
    -   `doRestoreFile`: Full restore single file.
    -   `doQuotaExceeded`.

### IBackupObserver.aidl / IRestoreObserver.aidl
-   **Role**: Callback interfaces for progress/status updates.

### IRestoreSession.aidl
-   **Role**: Session object for managing a restore flow.
-   **Methods**: `getAvailableRestoreSets`, `restoreAll`, `restorePackage`.

## Java-to-C++ Translation Guide
-   **Binder**: Implement/Call these interfaces using C++ Binder (`BnInterface`, `BpInterface`).
-   **Parcelables**: Ensure `BackupProgress`, `RestoreSet`, `RestoreDescription` parcelables match layout.
