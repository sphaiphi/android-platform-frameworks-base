# Downloads - Reverse Engineering Documentation

## Executive Summary
`Downloads` provides the contract for the `DownloadManager`'s underlying provider. It contains column definitions and status codes for the downloads database.

## Architecture Overview
- **Authority**: `downloads`.
- **Inner Class**: `Impl` (Contains the actual constants).

## Detailed Functionality
-   **Status Codes**: `STATUS_PENDING`, `STATUS_RUNNING`, `STATUS_SUCCESS`, `STATUS_FAILED`, etc.
-   **Columns**: `_DATA` (path), `URI`, `TITLE`, `DESCRIPTION`, `MIME_TYPE`, `TOTAL_BYTES`, `CURRENT_BYTES`.
-   **Control**: `COLUMN_CONTROL` (Run/Pause).
-   **Destination**: External, Cache Partition, etc.

## Java-to-C++ Translation Guide
-   **Status Mapping**: Map integer status codes to enums.
-   **URI**: `content://downloads/my_downloads` or `content://downloads/all_downloads`.
