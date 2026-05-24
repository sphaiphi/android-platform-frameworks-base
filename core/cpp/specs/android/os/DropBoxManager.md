# DropBoxManager - Reverse Engineering Documentation

## Executive Summary
`DropBoxManager` is a system service that records persistent log chunks ("entries") for later retrieval/debugging (like system crashes, kernel panics, or strict mode violations). It acts as a persistent, size-bounded log storage.

## Architecture Overview
-   **Role**: Persistent Logging.
-   **Service**: `IDropBoxManagerService`.
-   **Entry**: `DropBoxManager.Entry` encapsulates the data (text, byte array, or file).

## Detailed Functionality
-   **`addData` / `addText` / `addFile`**: Submits a new entry with a tag (e.g., "system_server_crash") and data.
-   **`getNextEntry(tag, msec)`**: Retrieves entries sequentially.
-   **Attributes**: Entries have timestamps and flags (IS_TEXT, IS_GZIPPED).

## Data Model
-   **Entry**:
    -   `mTag` (String)
    -   `mTimeMillis` (long)
    -   `mData` (byte[]) OR `mFileDescriptor` (ParcelFileDescriptor).

## Java-to-C++ Translation Guide
-   **Binder**: `IDropBoxManagerService`.
-   **Entry Marshalling**: The `Entry` class implements `Parcelable`. C++ needs to match this layout to read entries sent from Java, or to send entries to Java.
-   **File Descriptors**: Data often passed via PFD to avoid large binder transactions.

## Implementation Risks
-   **Spam**: `addText` is rate-limited and size-limited by the service.
-   **FD Leaks**: `Entry` must be closed to release the file descriptor.
