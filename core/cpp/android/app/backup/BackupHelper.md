# BackupHelper - Reverse Engineering Documentation

## Executive Summary
`BackupHelper` is the interface definition for modular backup components used by `BackupAgentHelper`. It defines the contract for backing up and restoring specific subsets of data.

## Architecture Overview
-   **Type**: Interface.
-   **Implementations**: `FileBackupHelper`, `SharedPreferencesBackupHelper`, `AbsoluteFileBackupHelper`, `BlobBackupHelper`.

## API Reference
-   **`performBackup(oldState, data, newState)`**: Backup logic.
-   **`restoreEntity(data)`**: Restore logic for a single entity.
-   **`writeNewStateDescription(newState)`**: Finalizes the state file after restore.

## Java-to-C++ Translation Guide
-   **Interface**: Pure virtual class in C++.

## Implementation Risks
-   **State Management**: Helpers must manage their state file descriptors carefully (don't close, don't read past their chunk).
