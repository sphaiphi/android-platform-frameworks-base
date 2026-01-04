# ApkSigningBlockUtils - Reverse Engineering Documentation

## Executive Summary
Shared utility methods for finding and parsing the APK Signing Block. This block sits between the ZIP Central Directory and the EoCD record.

## Architecture
*   **Block Format**:
    *   `size` (uint64)
    *   `ID-value pairs` (payload)
    *   `size` (uint64 - repeated)
    *   `magic` (16 bytes: "APK Sig Block 42")

## Key Algorithms
*   **`findSignature`**:
    *   Finds ZIP EoCD.
    *   Locates Central Directory start.
    *   Locates APK Signing Block immediately before Central Directory.
    *   Parses ID-value pairs to find the requested Block ID (V2/V3).
*   **`verifyIntegrity`**:
    *   Computes digests of the APK contents (excluding the signing block).
    *   Supports chunked hashing (1MB chunks) for parallelism and memory efficiency.
    *   Supports `verity` hashing (4KB Merkle tree).

## Java-to-C++ Translation Guide
*   **Memory Mapping**: Uses `mmap` (via `MemoryMappedFileDataSource`) to read large APKs efficiently.
*   **Digesting**: Manages multiple `MessageDigest` instances to compute different hashes (SHA-256, SHA-512) in one pass.