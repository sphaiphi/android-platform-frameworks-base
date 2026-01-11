# BackupDataInputStream - Reverse Engineering Documentation

## Executive Summary
`BackupDataInputStream` adapts the `BackupDataInput` interface to the standard Java `java.io.InputStream` interface. It restricts reading to the current entity's data size.

## Architecture Overview
-   **Inheritance**: `InputStream` -> `BackupDataInputStream`.
-   **Role**: Adapter.
-   **Dependencies**: `BackupDataInput`.

## Detailed Functionality
-   **`read()` / `read(byte[], int, int)`**: Delegates to `BackupDataInput.readEntityData`.
-   **Key/Size access**: Exposes `getKey()` and `size()` of the underlying entity.
-   **Constraint**: Does not support seeking or closing the underlying stream (as it's a shared sequential stream).

## Data Model
-   `mData`: Reference to `BackupDataInput`.
-   `dataSize`, `key`: Cached from the input.

## Java-to-C++ Translation Guide
-   **Stream Interface**: Map to `std::istream` or a custom stream class if C++ helpers expect standard stream interfaces.
-   **Delegation**: Simple delegation pattern.

## Implementation Risks
-   **Lifecycle**: The stream is ephemeral per entity. Ensure it's not used after the agent moves to the next entity.
