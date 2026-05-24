# SharedPreferencesBackupHelper - Reverse Engineering Documentation

## Executive Summary
`SharedPreferencesBackupHelper` backs up `SharedPreferences` XML files. It ensures the files are flushed to disk before backup and manages thread synchronization.

## Architecture Overview
-   **Inheritance**: `FileBackupHelperBase` -> `SharedPreferencesBackupHelper`.
-   **Role**: SharedPreferences specific backup.

## Detailed Functionality
-   **Backup**:
    -   Calls `QueuedWork.waitToFinish()` to flush in-memory prefs to disk.
    -   Resolves pref group names to file paths (`Context.getSharedPrefsFile`).
    -   Delegates to `performBackup_checked`.
-   **Restore**:
    -   Resolves key to file path.
    -   Delegates to `writeFile`.

## Java-to-C++ Translation Guide
-   **Synchronization**: The `QueuedWork` wait is Java-specific. In C++, if interacting with a custom prefs implementation, ensure persistence before backup. If backing up standard Android prefs from a native agent, this synchronization might be tricky (or implicit if the app is stopped).

## Implementation Risks
-   **Concurrency**: Backing up a file while it's being written to is the main risk.
