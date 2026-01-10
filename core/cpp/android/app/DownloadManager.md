# DownloadManager - Reverse Engineering Documentation

## Executive Summary
`DownloadManager` is a system service client that handles long-running HTTP downloads. It allows apps to enqueue download requests which are handled by a background system service (DownloadProvider/DownloadService). It also provides querying capabilities for download status.

## Architecture Overview
*   **Pattern**: Service Wrapper / ContentResolver Wrapper.
*   **Backend**: Relies on `DownloadProvider` (content provider) to store requests and status.

## Detailed Functionality

### Requesting Downloads (`enqueue`)
*   **Class**: `Request`.
*   **Config**: URI, destination (file path/Uri), headers, title, description, visibility, network constraints (WiFi/Mobile/Roaming/Metered).
*   **Mechanism**: Inserts a row into the `downloads` content provider. Returns the row ID.

### Querying (`query`)
*   **Class**: `Query`.
*   **Filter**: By ID, status (Pending, Running, Paused, Successful, Failed).
*   **Mechanism**: Performs a `ContentResolver.query` on the downloads provider and returns a `Cursor`.

### File Access
*   `openDownloadedFile(id)`: Returns `ParcelFileDescriptor`.
*   `getUriForDownloadedFile(id)`: Returns content URI.

### Actions
*   `remove(ids)`: Deletes rows (cancels downloads).
*   `restartDownload`, `pauseDownload`, `resumeDownload`.

## Data Model
*   **Columns**: `COLUMN_ID`, `COLUMN_TITLE`, `COLUMN_STATUS`, `COLUMN_REASON`, etc. (Constants mapping to provider columns).

## Java-to-C++ Translation Guide
*   **ContentResolver**: Heavily relies on ContentProvider contract (`insert`, `query`, `update`, `delete`). C++ implementation needs a `ContentResolver` proxy.
*   **Cursor**: Returns database cursors.

## Implementation Risks
*   **Database Schema**: Client must match the provider's schema expectations.
*   **Permissions**: `INTERNET`, `WRITE_EXTERNAL_STORAGE` (legacy).
