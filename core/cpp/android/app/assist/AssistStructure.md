# AssistStructure - Reverse Engineering Documentation

## Executive Summary
`AssistStructure` is a complex, heavy-weight Parcelable class that represents the entire view hierarchy of an Activity (or part of it) for Assist and Autofill purposes. It contains a tree of `WindowNode`s, each containing a tree of `ViewNode`s. It uses a custom Binder-based transfer mechanism (`SendChannel` / `ReceiveChannel`) to handle large data that exceeds standard IPC limits.

## Architecture Overview
- **Type**: Parcelable (with custom IPC transport).
- **Role**: View Hierarchy Snapshot.
- **Key Inner Classes**:
  - `WindowNode`: Represents a window (root).
  - `ViewNode`: Represents a single view.
  - `ViewNodeText`: text properties.
  - `SendChannel`/`ParcelTransferWriter`: Handles writing data over a separate Binder token if it's too large.
  - `ParcelTransferReader`: Handles reading the chunked data.

## Detailed Functionality

### Data Transfer Protocol (Custom Binder IPC)
Because view hierarchies can be huge, `AssistStructure` does not rely solely on the initial `writeToParcel`.
1.  **Initial Write**: Writes metadata (flags, times) and `mWindowNodes` count.
2.  **Chunked Write**: `ParcelTransferWriter` iterates through windows and views.
    -   It uses a `PooledStringWriter` to compress repetitive strings (package names, class names).
    -   If the `Parcel` fills up (checks `out.dataSize() > IBinder.MAX_IPC_SIZE`), it stops, writes a `SendChannel` binder token to the stream, and returns.
    -   The receiving side (`ParcelTransferReader`) reads until it finds the token, then calls `transact(TRANSACTION_XFER)` on that token to fetch the next chunk.
    -   This allows "infinite" size transfer via multiple IPC transactions.

### ViewNode Structure
-   Packed with flags to minimize size (`mFlags`, `mAutofillFlags`).
-   Contains positioning (`x`, `y`, `width`, `height`), matrix, elevation.
-   Contains content: Text, Hints, Autofill IDs/Values/Options, HTML info.
-   Contains hierarchy: `mChildren` array.

## Data Model (Simplified)

### AssistStructure
-   `mWindowNodes`: List of `WindowNode`.
-   `mAcquisitionStartTime`/`EndTime`: Timestamps.

### WindowNode
-   `mX`, `mY`, `mWidth`, `mHeight`, `mTitle`.
-   `mRoot`: Root `ViewNode`.

### ViewNode
-   Huge state object.
-   **Flags**: `mFlags` (int) encodes boolean properties (focusable, clickable, etc.) and presence of optional fields (has text, has children, etc.).
-   **Autofill Flags**: `mAutofillFlags` encodes autofill-specific field presence.
-   **Properties**: `mId`, `mClassName`, `mContentDescription`, `mText`, `mExtras`, etc.

## API Reference
-   `getWindowNodeAt(int)`
-   `getWindowNodeCount()`
-   `writeToParcel` / `createFromParcel`

## Java-to-C++ Translation Guide

### The Transport Protocol is Critical
-   **Do NOT** just implement a simple read/write.
-   **C++ Writer**: Must implement the `SendChannel` (BnBinder) logic to serve chunks when the client asks.
-   **C++ Reader**: Must implement the `ParcelTransferReader` logic to detect the token and request subsequent chunks.
-   **Pooled Strings**: Must implement the string pooling logic (write unique strings to a pool, write indices references) matching `PooledStringReader`/`Writer`.

### Bitmask Flags
-   The interpretation of `mFlags` and `mAutofillFlags` is bit-exact. C++ enums must match these constants exactly.

## Test Cases & Validation
-   **Large Hierarchy**: Create a deep/wide tree that exceeds 1MB parcel size. Verify it transfers correctly via the chunking mechanism.
-   **Pooling**: Verify repeated strings (e.g., "android.widget.TextView") are pooled and not written repeatedly.
-   **Flags**: Verify boolean properties are correctly packed/unpacked.

## Implementation Risks
-   **Complexity**: This is one of the most complex serialization logic sets in the framework due to the manual chunking and pooling.
-   **PooledStringWriter/Reader**: This dependency (`android.os.PooledStringWriter`) must be available or reimplemented in C++.

## Questions for C++ Team
-   Is `PooledStringReader`/`Writer` available in the C++ utils?
-   Is there existing infrastructure for the `SendChannel` pattern (Binder transaction loops) in the target C++ codebase?
