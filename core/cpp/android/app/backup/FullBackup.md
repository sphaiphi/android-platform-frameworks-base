# FullBackup - Reverse Engineering Documentation

## Executive Summary
`FullBackup` contains constants, definitions, and logic for the Full Backup (tarball) scheme. It handles parsing the XML rules (`android:fullBackupContent`) into a `BackupScheme` and applying them during backup/restore operations.

## Architecture Overview
-   **Role**: Logic Core / Constants / Configuration Parser.
-   **Inner Classes**: `BackupScheme`, `PathWithRequiredFlags`.

## Detailed Functionality

### Tokens & Prefixes
Defines tokens for semantic domains:
-   `f` (Files), `db` (Database), `sp` (SharedPrefs), `r` (Root), `ef` (External), etc.
-   `d_` prefix for Device Encrypted storage.

### Backup Scheme Parsing (`BackupScheme`)
-   **Input**: XML resource ID.
-   **Logic**:
    -   Parses `<include domain="..." path="..." requireFlags="..."/>` and `<exclude .../>`.
    -   Resolves domains to physical directory paths.
    -   Supports new `data-extraction-rules` (Android 12+) and legacy `full-backup-content`.
    -   Handles flag requirements (e.g., encryption).

### File Restoration (`restoreFile`)
-   **Purpose**: Writes data stream to file.
-   **Logic**:
    -   Reads from pipe.
    -   Writes to file.
    -   Sets metadata (`chmod` mode, `mtime`).
    -   Strips insecure permission bits (group/other RWX).

### Backup to Tar (`backupToTar`)
-   **Native Method**: `backupToTar`. Generates the tar stream.

## Java-to-C++ Translation Guide
-   **Constants**: Replicate string tokens exactly.
-   **XML Parsing**: Needs robust XML parsing.
-   **Domain Resolution**: Replicate logic mapping tokens (`db`) to paths (`/data/data/pkg/databases`).
-   **Tarball Generation**: The native `backupToTar` is already C++.

## Implementation Risks
-   **Path Traversal**: Canonical path checks are critical to prevent XML rules from escaping app directories (e.g., `..`).
-   **Permissions**: `restoreFile` must strictly sanitise file modes (mask `0700`).
