# LruCache - Reverse Engineering Documentation

## Executive Summary
A memory cache using a Least Recently Used (LRU) eviction policy.

## Architecture Overview
*   **Backing Store**: `java.util.LinkedHashMap` with access-ordering enabled (`true` in constructor). This automatically moves accessed items to the end of the list.
*   **Size Tracking**: Tracks current size against `maxSize`.

## Key Algorithms
*   **`get`**: Retrieves item. If missing, attempts `create()`. Updates usage order.
*   **`put`**: Adds item. Updates size. Triggers `trimToSize`.
*   **`trimToSize`**: Iterates from the head (eldest) of the `LinkedHashMap` and removes items until `size <= maxSize`. Calls `entryRemoved` for evictions.

## Java-to-C++ Translation Guide
*   **Implementation**: Can be implemented using `std::list` (for LRU order) + `std::unordered_map` (for lookup), or a custom combined structure.
*   **Synchronization**: The Java class uses `synchronized(this)`. C++ needs `std::mutex`.

## Implementation Risks
*   **Overhead**: `LinkedHashMap` node allocation overhead.
