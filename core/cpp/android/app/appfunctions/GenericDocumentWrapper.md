# GenericDocumentWrapper - Reverse Engineering Documentation

## Executive Summary
A specialized wrapper for `GenericDocument` (AppSearch) to optimize Parceling. It supports lazy unparceling and blob-based transfer to bypass Binder size limits.

## Architecture Overview
-   **Type**: Parcelable wrapper.
-   **Key Feature**: Lazy unparceling, Blob usage.

## Detailed Functionality

### Writing (`writeToParcel`)
1.  **If Document Exists**:
    -   Writes a placeholder for length.
    -   Marshalls the `GenericDocument` to a byte array.
    -   Writes bytes using `dest.writeBlob` (optimizes large data via shared memory if needed).
    -   Updates the length field.
2.  **If Wrapped Parcel Exists**:
    -   Writes original parcel data directly.

### Reading (`createFromParcel`)
1.  Reads length.
2.  Reads data from current position to length into a new `Parcel`.
3.  Stores the new Parcel for lazy decoding.

### Unparceling (`getValue`)
1.  Reads blob from stored Parcel.
2.  Unmarshalls bytes.
3.  Creates `GenericDocument` from bytes.

## Data Model
-   `mGenericDocument`: Cached object.
-   `mParcel`: Stored raw data.
-   `mDataSize`: Size cache.

## Java-to-C++ Translation Guide
-   **Blob Handling**: `Parcel::writeBlob` in C++ works similarly (Ashmem/Binder).
-   **Lazy Logic**: Replicate the lazy parsing to avoid overhead if data isn't accessed.

## Implementation Risks
-   **Binder Limits**: The primary purpose is handling size limits; validation of this behavior is critical.
-   **Concurrency**: Uses `synchronized(mLock)`; C++ needs `std::mutex`.
