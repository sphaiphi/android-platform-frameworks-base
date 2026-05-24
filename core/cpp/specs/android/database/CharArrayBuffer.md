# CharArrayBuffer - Reverse Engineering Documentation

## Executive Summary
`CharArrayBuffer` is a simple mutable container for `char[]` data, used to reduce memory allocations when reading large amounts of text from a cursor.

## Data Model
*   `char[] data`: The buffer.
*   `int sizeCopied`: Actual length of valid data in `data`.

## Java-to-C++ Translation Guide
*   **Equivalent**: `std::vector<char>` or a struct with `char*` and length.
*   **Usage**: Used in `copyStringToBuffer`.
