# ArrayMap - Reverse Engineering Documentation

## Executive Summary
`ArrayMap` is a generic key-value mapping data structure designed to be more memory-efficient than `java.util.HashMap`. It stores mappings in two arrays: one for hashes and one for key/value pairs. It optimizes for space at the cost of execution speed (using binary search), making it suitable for small numbers of items (up to hundreds).

## Architecture Overview
*   **Implements**: `java.util.Map`.
*   **Storage**: Two parallel arrays:
    *   `mHashes`: Sorted array of integer hash codes.
    *   `mArray`: Array of Objects, storing keys and values interleaved (`key` at `index<<1`, `value` at `(index<<1)+1`).
*   **Caching**: Uses static caches (`mBaseCache`, `mTwiceBaseCache`) to recycle small arrays (sizes 4 and 8) to reduce GC pressure.

## Key Algorithms

### Lookups (`indexOfKey`, `indexOfValue`)
*   **Key Lookup**: Uses binary search on `mHashes` to find the index of the hash code. If multiple keys have the same hash (collision), it linearly searches adjacent entries in `mArray` to find the exact key equality.
*   **Value Lookup**: Performs a linear scan of `mArray` (odd indices).

### Insertions (`put`, `append`)
*   **Growth**: If the array is full, it grows.
    *   Size < 4 -> 4
    *   Size < 8 -> 8
    *   Size >= 8 -> Size * 1.5
*   **Insertion**: Finds the insertion index via binary search. If the key doesn't exist, shifts elements in `mHashes` and `mArray` to make room, then inserts the new hash and key/value pair.

### Deletions (`removeAt`)
*   **Shrinking**: If the array utilization drops below 1/3, it shrinks the arrays (but not smaller than 8) to save memory.
*   **Shifting**: Shifts elements to fill the gap left by the removed item.

### Caching
*   **Alloc**: Checks static caches first. If available, reuses the array.
*   **Free**: When arrays of size 4 or 8 are freed, they are linked into the static cache (up to `CACHE_SIZE = 10`).

## Java-to-C++ Translation Guide
*   **Data Structure**: Corresponds to `std::vector` or a flat map implementation (e.g., `boost::flat_map` or `folly::flat_map`), but with the specific split-array layout of Android.
*   **Caching**: The static cache mechanism is specific to Java's object allocation cost. In C++, standard allocators or a custom slab allocator might be used, but manual array caching is less critical if using `std::vector`.
*   **Concurrency**: NOT thread-safe. C++ implementation requires external synchronization.
*   **Generic Types**: Java uses `Object[]`. C++ would likely use templates `ArrayMap<K, V>`.

## Implementation Risks
*   **Performance**: O(N) insertion/deletion and O(log N) lookup. Do not use for large datasets.
*   **Concurrent Modification**: Throws `ConcurrentModificationException` on best-effort basis.
