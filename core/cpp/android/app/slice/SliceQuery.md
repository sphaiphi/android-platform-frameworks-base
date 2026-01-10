# SliceQuery - Reverse Engineering Documentation

## Executive Summary
`SliceQuery` is a utility class for traversing and searching the `Slice` tree structure. It provides methods to find items based on format, hints, and subtypes.

## Architecture Overview
*   **Package**: `android.app.slice`
*   **Type**: Static Utility Class.
*   **Role**: Helper for parsing Slices.

## Detailed Functionality

### 1. Tree Traversal (`stream`)
**Algorithm**:
1.  Initialize a Queue with the root `SliceItem`.
2.  While Queue is not empty:
    *   Dequeue item.
    *   Yield item.
    *   If item format is `SLICE` or `ACTION`:
        *   Retrieve children (`item.getSlice().getItems()`)
        *   Enqueue all children.
**Result**: A Flattened stream of items (Breadth-First Search order).

### 2. Search (`find` / `findAll`)
**Criteria**:
*   **Type**: Matches `getFormat()`. Supports subtypes via slash notation (e.g., "text/message"). Wildcard `*/*` matches all.
*   **Hints**: Must contain ALL specified hints.
*   **NonHints**: Must NOT contain ANY of the specified non-hints.

**Logic**:
*   `find`: Returns the first match from the stream.
*   `findAll`: Returns a list of all matches.

### 3. Primary Icon Detection (`getPrimaryIcon`)
**Heuristic**:
1.  Iterate direct children.
2.  Return first `FORMAT_IMAGE`.
3.  Fallback: Look inside children, but SKIP items with hints `LIST`, `ACTIONS`, or format `ACTION`.
4.  Recursively `find` image in allowed children.

## API Reference
*   `find(Slice, String type, String[] hints, String[] nonHints)`
*   `findAll(SliceItem, String type, ...)`
*   `stream(SliceItem)`

## Java-to-C++ Translation Guide

### Iterators
*   Java uses `Stream` and `Spliterators`.
*   C++: Implement a standard `Iterator` or `Generator` that performs the BFS queue logic.

### String Matching
*   `compareTypes` uses Regex replacement (`replaceAll("\\*", ".*")`) then matches.
*   **Optimization**: C++ implementation should probably avoid compiling a regex for every comparison. Simple string parsing (split at '/') is likely sufficient and faster.

## Test Cases
*   **Search**: Create a tree: Root -> [Text A, Slice B -> [Text C, Icon D]].
    *   `find(text)` should return A.
    *   `findAll(text)` should return [A, C].
*   **Primary Icon**: Verify the exclusion logic (ignoring actions/lists).

## Implementation Risks
*   **Performance**: The `stream` creates a new `LinkedList` and `Iterator` object. In C++, avoid excessive allocation; use `std::deque`.
