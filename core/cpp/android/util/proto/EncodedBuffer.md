# EncodedBuffer - Reverse Engineering Documentation

## Executive Summary
`EncodedBuffer` is a low-level buffer management class for the `ProtoOutputStream`. It manages a list of fixed-size byte arrays ("chunks") to provide a growable output stream without large contiguous allocations.

## Architecture
*   **Chunks**: Uses `ArrayList<byte[]>` (`mBuffers`) to store data.
*   **Cursors**:
    *   Write: `mWriteBuffer`, `mWriteIndex`, `mWriteBufIndex`.
    *   Read: `mReadBuffer`, `mReadIndex`, `mReadBufIndex`.
*   **Rewind**: Supports `startEditing()` to rewind pointers for the multipass encoding used by `ProtoOutputStream`.

## Key Algorithms
*   **`writeRawByte`**: Writes a byte. If the current chunk is full, allocates/fetches the next chunk.
*   **`readRawUnsigned`**: Reads a varint.
*   **`getRawVarint32Size`**: Static helper to calculate varint size.

## Java-to-C++ Translation Guide
*   **IOBuf**: This structure is very similar to `folly::IOBuf` or a deque of vectors.
*   **Pointers**: C++ implementation would likely use raw pointers for current read/write positions for speed.
