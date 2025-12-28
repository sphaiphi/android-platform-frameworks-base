# FileBackupHelperBase - Reverse Engineering Documentation

## Executive Summary
`FileBackupHelperBase` provides the shared native implementation for file-based backup helpers (`FileBackupHelper`, `AbsoluteFileBackupHelper`, etc.). It manages the JNI calls to perform file system scans, diffs against state, and writing restored files.

## Architecture Overview
-   **Role**: Native Interface Wrapper.
-   **Dependencies**: Native methods.

## Detailed Functionality
-   **`performBackup_checked`**: Validates arguments (absolute paths) and calls `performBackup_native`.
-   **`writeFile`**: Ensures parent directories exist, then calls `writeFile_native` to pipe data from `BackupDataInputStream` (via its reader handle) to the file.
-   **`writeNewStateDescription`**: Calls `writeSnapshot_native`.

## Data Model
-   `mPtr`: Native pointer to the underlying C++ helper object.

## Java-to-C++ Translation Guide
-   **Native Impl**: The "native" methods here correspond to `android_app_backup_FileBackupHelper.cpp` in `frameworks/base`. The C++ team should reference that existing implementation directly.

## Implementation Risks
-   **Directory Creation**: `mkdirs()` is done in Java. C++ rewrite needs to handle recursive directory creation (`mkdir -p`).
