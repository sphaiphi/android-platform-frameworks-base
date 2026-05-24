# AtomicFile - Reverse Engineering Documentation

## Executive Summary
`AtomicFile` provides file integrity by using a backup file ("journaling" style). Write operations are performed on a temporary file, which is renamed to the destination file upon success.

## Architecture Overview
*   **Files**:
    *   `mBaseName`: The target file.
    *   `mNewName`: `mBaseName` + ".new" (Temporary write file).
    *   `mLegacyBackupName`: `mBaseName` + ".bak" (Backup for rollback).

## Key Algorithms
*   **`startWrite()`**:
    *   If a backup file exists, rename it to the base file (restoring previous state if a crash occurred).
    *   Returns a `FileOutputStream` to `mNewName`.
*   **`finishWrite()`**:
    *   Syncs (fsync) the stream.
    *   Closes stream.
    *   Renames `mNewName` to `mBaseName` (atomic operation).
    *   Deletes backup if needed (though implementation details in `rename` handles the overwrite).
*   **`failWrite()`**:
    *   Syncs and closes stream.
    *   Deletes `mNewName`, preserving `mBaseName`.
*   **`openRead()`**:
    *   If backup exists, restores it to base name.
    *   If new file exists but base doesn't (crash during first write), deletes new file.
    *   Returns stream for `mBaseName`.

## Java-to-C++ Translation Guide
*   **File I/O**: Maps to standard C++ `fstream` or POSIX `open`/`write`/`fsync`/`rename`.
*   **Atomicity**: `rename` syscall is critical here.

## Implementation Risks
*   **Concurrency**: NOT thread-safe. Caller must ensure external locking.
