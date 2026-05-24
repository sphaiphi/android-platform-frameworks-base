# BaseBundle - Reverse Engineering Documentation

## Executive Summary
`BaseBundle` is the foundational mapping class for `Bundle` and `PersistableBundle`. It manages a string-keyed map of values (`ArrayMap<String, Object>`). It handles lazy deserialization (unparceling) from a `Parcel`, allowing data to remain packed until accessed.

## Architecture Overview
-   **Pattern**: Dictionary / Map / Lazy Deserializer.
-   **State**: Can exist in two states:
    1.  **Parcelled**: Data resides in `mParcelledData` (raw bytes). `mMap` is null.
    2.  **Unparcelled**: Data resides in `mMap`. `mParcelledData` is recycled (or kept weak referenced).
-   **Concurrency**: Uses `synchronized (this)` for thread safety during unparceling.

## Detailed Functionality

### Lazy Unparceling
-   **Mechanism**: Methods like `size()`, `isEmpty()`, `containsKey()` call `unparcel()`.
-   **`unparcel()`**: Reads the `Parcel`. The format includes a magic number (`BUNDLE_MAGIC` or `BUNDLE_MAGIC_NATIVE`), count, and then the map data.
-   **Defusing**: If `setShouldDefuse(true)` is set (usually in system server), `BadParcelableException` during unparceling is logged and swallowed to prevent crashing the system.

### Data Types
-   Supports Primitives (via `Parcel`), String, CharSequence, Serializable, ArrayList, and specific Arrays.
-   **Magic Numbers**:
    -   `0x4C444E42` ('B' 'N' 'D' 'L'): Java Bundle.
    -   `0x4C444E44` ('B' 'N' 'D' 'N'): Native Bundle (C++).

## Java-to-C++ Translation Guide
-   **C++ Equivalent**: `android::os::Bundle` (binder).
-   **Serialization**: The binary format is:
    1.  Length (int)
    2.  Magic (int)
    3.  Map Data (ArrayMap format: Count, then Key-Value pairs).
-   **Locking**: C++ implementation must handle thread-safe lazy unpacking if copying the lazy-behavior.

## Implementation Risks
-   **Lazy Values**: `unwrapLazyValueFromMapLocked` handles partial deserialization (e.g. `LazyValue` objects inside the map). C++ implementation might not support this granular lazy loading as easily.
-   **Resource Management**: Recycling `Parcel` objects (`mParcelledData`) is critical for memory efficiency.
