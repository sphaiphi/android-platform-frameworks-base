# BackupDataOutput - Reverse Engineering Documentation

## Executive Summary
`BackupDataOutput` provides the interface for writing backup entities to the backup transport stream. It handles writing headers (keys, sizes) and data payloads.

## Architecture Overview
-   **Role**: Data Writer.
-   **Dependencies**: Native methods (`writeEntityHeader_native`, `writeEntityData_native`).
-   **Usage**: Used within `BackupAgent.onBackup` to write entities.

## Detailed Functionality

### Initialization
-   **Constructor**: Takes `FileDescriptor`, `quota`, and `transportFlags`. Calls native `ctor`.
-   **Native State**: Holds `mBackupWriter` pointer.

### Writing Entities
-   **`writeEntityHeader(String key, int dataSize)`**: Starts a new entity. Key must be unique. `dataSize = -1` implies deletion.
-   **`writeEntityData(byte[], int)`**: Writes payload data. Can be chunked.
-   **`setKeyPrefix(String)`**: Sets a prefix applied to all subsequent keys (used by `BackupHelperDispatcher`).

## Data Model
-   `mBackupWriter`: `long` (native pointer).
-   `mQuota`: Max bytes allowed.
-   `mTransportFlags`: Properties of the transport.

## Java-to-C++ Translation Guide
-   **Native Implementation**: Thin wrapper around `android::BackupDataOutput` (C++). Use the existing C++ implementation.

## Implementation Risks
-   **Protocol**: Must strictly follow the header -> data -> header sequence.
