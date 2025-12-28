# AbsoluteFileBackupHelper - Reverse Engineering Documentation

## Executive Summary
`AbsoluteFileBackupHelper` is a specialized backup helper for persisting and restoring specific files identified by their absolute filesystem paths. It extends the functionality of `FileBackupHelperBase` to handle direct file paths rather than paths relative to the application's files directory.

## Architecture Overview
-   **Inheritance**: `Object` -> `FileBackupHelperBase` -> `AbsoluteFileBackupHelper`.
-   **Implements**: `BackupHelper`.
-   **Role**: Helper component for `BackupAgentHelper` to manage absolute file paths.
-   **Key Dependencies**:
    -   `FileBackupHelperBase`: Provides core native file I/O operations (`performBackup_native`, `writeFile_native`).
    -   `BackupDataOutput`, `BackupDataInputStream`: Streams for writing/reading backup entities.

## Detailed Functionality

### Backup Logic (`performBackup`)
**Purpose**: Saves the current state of specified absolute files if they have changed.
**Algorithm**:
1.  Delegates directly to `FileBackupHelperBase.performBackup_checked`.
2.  Passes the raw `mFiles` array (absolute paths) as both the file paths to read and the backup keys to store.
3.  The native layer checks file metadata against `oldState` and writes diffs to `data` and updates `newState`.

### Restore Logic (`restoreEntity`)
**Purpose**: Restores a file from the backup stream to its absolute location.
**Algorithm**:
1.  Reads the entity key from `BackupDataInputStream`.
2.  Verifies the key exists in the configured `mFiles` list (`isKeyInList`).
3.  If valid, creates a `File` object using the key (which is the absolute path).
4.  Calls `writeFile` (inherited) to write the data stream to disk.

## Data Model
-   `mFiles`: `String[]` of absolute paths managed by this helper.

## API Reference
-   `AbsoluteFileBackupHelper(Context context, String... files)`: Constructor.
-   `performBackup(ParcelFileDescriptor, BackupDataOutput, ParcelFileDescriptor)`: Backup entry point.
-   `restoreEntity(BackupDataInputStream)`: Restore entry point.

## Java-to-C++ Translation Guide
-   **Native Integration**: This class relies heavily on `FileBackupHelperBase`. Ensure the native implementation of `performBackup_checked` (and its underlying `performBackup_native`) and `writeFile_native` handles absolute paths correctly (which Java enforces).
-   **String Handling**: Java strings -> C++ strings (UTF-8).
-   **File I/O**: Use standard POSIX file operations in C++ equivalent of the base class.

## Implementation Risks
-   **Absolute Paths**: Writing to absolute paths during restore is dangerous. The helper validates the key is in the constructed list, but the native `writeFile` must ensure it doesn't traverse symlinks inappropriately if running with elevated privileges (though standard apps run as their own UID).
-   **Permissions**: Ensure the process has write access to the absolute paths specified.

## Questions for C++ Team
-   Does the native backup infrastructure already support the arbitrary path/key mapping used here (where key == absolute path)?
