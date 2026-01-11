# SparseIntArray - Reverse Engineering Documentation

## Executive Summary
A map of `int` -> `int`. Primitive version of `SparseArray`.

## Architecture Overview
*   **Storage**: `int[] mKeys`, `int[] mValues`.
*   **Difference from SparseArray**: No garbage collection (lazy deletion) mechanism is visible in the provided code snippet (unlike SparseArray/LongSparseArray). Deletions seem to shift immediately (`removeAt`).

## Key Algorithms
*   **Lookup**: Binary search.
*   **Insertion**: Binary search + Shift.

## Java-to-C++ Translation Guide
*   **Equivalent**: `std::vector<std::pair<int, int>>` sorted, or `flat_map`.
