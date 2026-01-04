# EntityConfidence - Reverse Engineering Documentation

## Executive Summary
Helper class to manage entity confidence scores. It maps entity strings (e.g., "address", "phone") to float scores (0.0-1.0) and maintains a sorted list of entities by confidence.

## Logic
*   **Storage**: `ArrayMap<String, Float>`.
*   **Sorting**: `mSortedEntities` list is kept sorted based on the map values.
*   **Clamping**: Values > 1 are clamped to 1. Values <= 0 are ignored/removed.

## Java-to-C++ Translation Guide
*   **Map**: `std::map` or `std::vector` of pairs.
*   **Sorting**: `std::sort`.
