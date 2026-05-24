# BackupAnnotations - Reverse Engineering Documentation

## Executive Summary
`BackupAnnotations` is a utility class defining integer definition (`@IntDef`) annotations for type safety within the backup framework. It defines constants for operation types and backup destinations.

## Architecture Overview
-   **Type**: Utility / Definition class.
-   **Role**: compile-time type checking definitions.

## Detailed Functionality
-   **OperationType**: `UNKNOWN` (-1), `BACKUP` (0), `RESTORE` (1).
-   **BackupDestination**: `CLOUD` (0), `DEVICE_TRANSFER` (1), `ADB_BACKUP` (2).

## Data Model
-   Static integer constants.

## API Reference
-   `@OperationType`
-   `@BackupDestination`

## Java-to-C++ Translation Guide
-   **Enums**: Map these `@IntDef` groups to C++ `enum class` or standard `enum` to ensure type safety in the native layer.

## Implementation Risks
-   None. Pure constant definitions.
