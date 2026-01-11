# ArraySet - Reverse Engineering Documentation

## Executive Summary
`ArraySet` is a generic set data structure designed to be memory-efficient. It mirrors the design of `ArrayMap` but stores only keys.

## Architecture Overview
*   **Implements**: `java.util.Collection`, `java.util.Set`.
*   **Storage**:
    *   `mHashes`: Sorted array of integer hash codes.
    *   `mArray`: Array of Objects storing the elements.
*   **Caching**: Shares the same caching logic logic (conceptually) as `ArrayMap` for small array reuse.

## Key Algorithms
*   **Lookup**: Binary search on `mHashes`.
*   **Growth/Shrink**: Same policies as `ArrayMap` (Base size 4, doubling/1.5x growth, shrinking at 1/3 load).

## Java-to-C++ Translation Guide
*   **Equivalent**: `std::vector` with sorted insertions + `std::unique`, or `boost::flat_set`.
*   **Memory**: Tries to avoid the node overhead of `std::set` (Red-Black tree).

## Implementation Risks
*   **Performance**: O(N) insert/delete. Good for small sets.
