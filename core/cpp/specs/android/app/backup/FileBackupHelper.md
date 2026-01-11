# FileBackupHelper - Reverse Engineering Documentation

## Executive Summary
`FileBackupHelper` is a concrete implementation of `FileBackupHelperBase` for backing up files relative to the application's `files` directory (`Context.getFilesDir()`).

## Architecture Overview
-   **Inheritance**: `FileBackupHelperBase` -> `FileBackupHelper`.
-   **Role**: Simple file backup helper.

## Detailed Functionality
-   **Construction**: Accepts a list of filenames (relative to `files/`).
-   **Backup**: Converts relative paths to absolute paths (`mFilesDir` + filename) and calls `performBackup_checked`.
-   **Restore**: Checks if entity key matches a valid file. Constructs destination path and calls `writeFile`.

## Java-to-C++ Translation Guide
-   Trivial wrapper around `FileBackupHelperBase`. Logic is mostly path string manipulation.

## Implementation Risks
-   None.
