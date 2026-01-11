# SparseArray - Reverse Engineering Documentation

## Executive Summary
A map of `int` -> `Object`. optimized for memory.

## Architecture Overview
*   **Storage**: Two arrays: `int[] mKeys` and `Object[] mValues`.
*   **Deleted State**: Uses a sentinel object `DELETED` to mark removals, avoiding immediate array compaction ("lazy deletion").

## Key Algorithms
*   **Lookup**: Binary search on `mKeys`.
*   **Garbage Collection**: A `gc()` method compacts the arrays (removing `DELETED` entries) when necessary (e.g., on insert or size query).
*   **Insertion**: Binary search. If key found, replace value. If not found, insert at sorted position (shifting elements).

## Java-to-C++ Translation Guide
*   **Equivalent**: `std::map<int, T>` is node-based and heavier. `flat_map` is closer.
*   **Lazy Deletion**: This is a specific optimization to avoid `memmove` on every delete.

## Implementation Risks
*   **Performance**: Binary search is faster than hashing for small arrays but slower for large ones.
