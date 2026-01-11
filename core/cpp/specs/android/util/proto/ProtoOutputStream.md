# ProtoOutputStream - Reverse Engineering Documentation

## Executive Summary
Writes Protocol Buffers. Designed to avoid object allocation overhead of standard Protobuf generated classes.

## Architecture
*   **Multi-pass Encoding**:
    1.  **Pass 1**: Writes data to `EncodedBuffer` (chunked byte arrays). Nested object sizes are unknown, so placeholders (sentinels) are written.
    2.  **Pass 2**: Recursively calculates sizes of nested objects.
    3.  **Pass 3**: Compacts the buffer, writing the varint sizes into the reserved spaces.
*   **EncodedBuffer**: A linked list of fixed-size byte arrays to minimize GC churn.

## Key Algorithms
*   **`write`**: Appends tag and value.
*   **`start(fieldId)`**: Appends tag. Reserves 4 bytes for size. Pushes state to stack. Returns a token.
*   **`end(token)`**: Pops stack. Calculates size of the nested object. If size fits in reserved space, writes it. If not (or if compaction is needed), marks for later processing.

## Java-to-C++ Translation Guide
*   **Memory Management**: `EncodedBuffer` logic is similar to `std::deque<std::vector<uint8_t>>` or `IOBuf`.
*   **Compaction**: The multi-pass size calculation is a specific optimization to avoid pre-calculating sizes in a separate object tree.
