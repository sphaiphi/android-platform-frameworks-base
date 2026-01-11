# BackupHelperDispatcher - Reverse Engineering Documentation

## Executive Summary
`BackupHelperDispatcher` manages the multiplexing of multiple `BackupHelper` instances onto a single backup stream. It handles state file chunking so each helper sees only its own state, and prefixes entity keys to namespace them per helper.

## Architecture Overview
-   **Role**: Multiplexer / Controller.
-   **Data Structure**: `TreeMap<String, BackupHelper>` maps key prefixes to helpers.
-   **Dependencies**: Native methods for reading/writing state file headers (`readHeader_native`, `allocateHeader_native`, etc.).

## Detailed Functionality

### Backup (`performBackup`)
**Algorithm**:
1.  **Old State Pass**: Reads the old state file header-by-header.
    -   Reads a header containing `chunkSize` and `keyPrefix`.
    -   If a helper exists for `keyPrefix`: Calls `helper.performBackup` using the current file position. Removes helper from the "pending" list.
    -   If no helper: Skips the chunk (`skipChunk_native`).
2.  **New Helpers Pass**: Iterates remaining helpers (those not found in old state).
    -   Calls `doOneBackup` for each.

### Helper Execution (`doOneBackup`)
1.  Allocates space for a header in `newState` (`allocateHeader_native`).
2.  Sets the key prefix on `BackupDataOutput`.
3.  Calls `helper.performBackup`.
4.  Writes the header (with calculated chunk size) back to the allocated position (`writeHeader_native`).

### Restore (`performRestore`)
**Algorithm**:
1.  Iterates entities in `BackupDataInput`.
2.  Parses raw key: checks for `prefix:entityKey` format.
3.  Lookups helper by `prefix`.
4.  If found: Calls `helper.restoreEntity`.
5.  Else: Logs warning, skips entity.
6.  Finally: Calls `writeNewStateDescription` for all registered helpers to generate a fresh state file.

## Data Model
-   `mHelpers`: `TreeMap` (ensures consistent order).
-   `Header` (inner class): Maps to native struct.

## Java-to-C++ Translation Guide
-   **State File Format**: The native methods imply a specific binary format for the state file (header + blob). This format must be bit-exact in C++.
-   **Key Prefixing**: The logic `prefix + ":" + key` is hardcoded here and used during restore.

## Implementation Risks
-   **State File Corruption**: If `doOneBackup` fails to update the header size correctly, the state file becomes corrupt.
-   **File Descriptors**: Shared usage of FDs requires careful seeking/positioning.
