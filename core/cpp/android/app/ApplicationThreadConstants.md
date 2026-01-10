# ApplicationThreadConstants - Reverse Engineering Documentation

## Executive Summary
`ApplicationThreadConstants` defines integer constants used for communication between the system server and the application thread (via `IApplicationThread`).

## Constants
### Backup Modes
*   `BACKUP_MODE_INCREMENTAL` (0)
*   `BACKUP_MODE_FULL` (1)
*   `BACKUP_MODE_RESTORE` (2)
*   `BACKUP_MODE_RESTORE_FULL` (3)

### Debug Modes
*   `DEBUG_OFF` (0)
*   `DEBUG_ON` (1)
*   `DEBUG_WAIT` (2)
*   `DEBUG_SUSPEND` (3)

### Package States
*   `PACKAGE_REMOVED` (0)
*   `EXTERNAL_STORAGE_UNAVAILABLE` (1)
*   `PACKAGE_REMOVED_DONT_KILL` (2)
*   `PACKAGE_REPLACED` (3)

## Java-to-C++ Translation Guide
*   Map to `enum` or `constexpr int`.
