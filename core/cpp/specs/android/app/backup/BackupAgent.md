# BackupAgent - Reverse Engineering Documentation

## Executive Summary
`BackupAgent` is the central abstract class that applications extend to communicate with the Android backup infrastructure. It provides the interface for backing up and restoring application data, handling both key/value pairs and full filesystem backups. It manages the lifecycle of the backup operation, threading (handling Binder callbacks), and integration with the system service.

## Architecture Overview
-   **Inheritance**: `ContextWrapper` -> `BackupAgent`.
-   **Role**: Application-side entry point for backup/restore.
-   **Binder Interface**: `IBackupAgent.Stub` (implemented internally as `BackupServiceBinder`).
-   **Threading**:
    -   `onCreate`/`onDestroy`: Main (UI) thread.
    -   `onBackup`/`onRestore`/`onFullBackup`: Binder pool threads.
-   **Key Components**:
    -   `BackupServiceBinder`: Handles IPC calls from `BackupManagerService`.
    -   `BackupDataOutput`/`BackupDataInput`: Interfaces for key/value data streams.
    -   `FullBackupDataOutput`: Interface for full backup data streams.
    -   `FullBackup.BackupScheme`: Logic for parsing `android:fullBackupContent` XML rules.

## Detailed Functionality

### Lifecycle & Initialization
-   **`onCreate`**: Called when the agent is instantiated. Can be overloaded to receive `UserHandle` and `BackupDestination`.
-   **`onDestroy`**: Cleanup hook.
-   **`attach`**: Attaches the base context (standard ContextWrapper pattern).

### Key/Value Backup (`onBackup`)
-   **Abstract Method**: Apps must implement this.
-   **Mechanism**: Read old state blob, write differences to `BackupDataOutput`, write new state blob.
-   **Incremental**: Relies on state files to detect changes.

### Key/Value Restore (`onRestore`)
-   **Abstract Method**: Apps must implement this.
-   **Mechanism**: Iterates `BackupDataInput` entities and applies them.
-   **Excluded Keys**: Supports excluding specific keys from restore (e.g., if set by system policy).

### Full Backup (`onFullBackup`)
-   **Default Implementation**: Traverses app directories (`files`, `shared_prefs`, `db`, etc.) and streams them to tarball via `FullBackup.backupToTar`.
-   **XML Rules**: Parses `res/xml` (defined in manifest) to include/exclude specific files/domains using `FullBackup.BackupScheme`.
-   **Encryption/Device-Transfer**: Respects transport flags to enforce encryption requirements.

### Full Restore (`onRestoreFile`)
-   **Mechanism**: Receives file data from a pipe (`ParcelFileDescriptor`).
-   **Default Implementation**: Writes data to disk, validating against XML rules (`isFileEligibleForRestore`). Handles cross-domain mapping if necessary.

### Quota Management
-   `onQuotaExceeded`: Callback if data size exceeds transport limits.

### Helper Methods
-   `fullBackupFile`: Backs up a single file to the full backup stream.
-   `fullBackupFileTree`: Recursively backs up a directory tree.

## Data Model
-   **Constants**: `TYPE_FILE`, `TYPE_DIRECTORY`, `FLAG_CLIENT_SIDE_ENCRYPTION_ENABLED`, etc.
-   **Internal State**: `UserHandle mUser`, `int mBackupDestination`, `BackupRestoreEventLogger mLogger`.

## API Reference
-   `onBackup(...)`: Abstract.
-   `onRestore(...)`: Abstract.
-   `onFullBackup(...)`: Overridable default provided.
-   `onRestoreFile(...)`: Overridable default provided.
-   `fullBackupFile(...)`: Utility.

## Java-to-C++ Translation Guide
-   **Binder**: The `BackupServiceBinder` inner class is the IPC interface. This must be implemented as a native Binder object (`BnBackupAgent`).
-   **Context**: As a `ContextWrapper`, it relies on an Android Context. In pure C++, this context might be an abstract environment or config object.
-   **XML Parsing**: The full backup logic relies heavily on `XmlPullParser` for configuration. C++ needs an equivalent XML parser to interpret backup schemes.
-   **File I/O**: Uses `java.io.File`, `FileInputStream`, `FileOutputStream`. Map to `std::fstream` or POSIX I/O.
-   **Concurrency**: Uses `CountDownLatch` and `Handler` for thread synchronization (SharedPrefs). C++ equivalents are `std::latch` (C++20) or `std::condition_variable`, and `Looper`/`Handler` equivalent if available or `std::thread`.

## Implementation Risks
-   **XML Compatibility**: The XML parsing logic (`BackupScheme`, `IncludeExcludeRules`) is complex and defines security boundaries (what gets backed up). Exact parity is crucial to prevent data leaks.
-   **Threading**: Ensuring operations happen on the correct threads (main vs binder) is critical for system stability.
-   **Binder Interface**: `IBackupAgent.aidl` methods (`doBackup`, `doRestore`, etc.) must be strictly adhered to.

## Questions for C++ Team
-   Is there a `SharedPreferences` equivalent in the C++ layer that needs synchronization?
-   Do we need to support the full `XmlResourceParser` capabilities or just standard XML?
