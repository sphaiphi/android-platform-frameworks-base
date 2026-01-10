# BlobBackupHelper - Reverse Engineering Documentation

## Executive Summary
`BlobBackupHelper` is a backup helper designed for handling large opaque binary blobs (byte arrays). It features built-in versioning, compression (zlib), and diff detection (CRC32 checksums) to optimize backup size and bandwidth.

## Architecture Overview
-   **Inheritance**: `BackupHelperWithLogger` -> `BlobBackupHelper`.
-   **Role**: Helper for binary blobs.
-   **Key Dependencies**: `DeflaterOutputStream` / `InflaterInputStream` (zlib).

## Detailed Functionality

### Backup (`performBackup`)
**Algorithm**:
1.  **State Reading**: Reads the old state file containing (key, checksum) pairs.
2.  **Iterate Keys**: For each key in the constructor:
    -   Calls `getBackupPayload(key)` (abstract method implemented by subclass).
    -   Compresses payload (`deflate`) -> writes header version.
    -   Calculates CRC32 checksum of compressed data.
    -   **Diff Check**: Compares calculated checksum with `oldState` checksum.
    -   **Write**: If different, writes header and compressed data to `BackupDataOutput`. If payload null, writes deletion.
    -   **Update State**: Updates `newState` map with new checksum.
3.  **State Writing**: Writes `newState` to `newStateFd`.

### Restore (`restoreEntity`)
**Algorithm**:
1.  Reads compressed data from stream.
2.  Decompresses (`inflate`).
    -   Checks version header in stream. Aborts if version > current.
3.  Calls `applyRestoredPayload(key, payload)` (abstract method).

## Data Model
-   **State File Format**:
    -   Int: Version
    -   Int: N (count)
    -   N * (String key, Long checksum)
-   **Blob Format**:
    -   Int: Version
    -   Compressed Data (zlib)

## API Reference
-   `getBackupPayload(String)`: Abstract.
-   `applyRestoredPayload(String, byte[])`: Abstract.

## Java-to-C++ Translation Guide
-   **Zlib**: Use `zlib` directly in C++.
-   **DataInputStream/OutputStream**: Use standard C++ serialization for integers/strings.
-   **Map**: `std::map<std::string, int64_t>` for state.

## Implementation Risks
-   **Compression Compatibility**: Ensure zlib parameters match Java's defaults to ensure compatibility if data migrates between impls.
-   **Endianness**: Java `DataOutputStream` is Big-Endian. C++ implementation must ensure Big-Endian read/write for the state file and blob headers.
