# AccessibilityCache - Reverse Engineering Documentation

## Executive Summary
Caching mechanism for `AccessibilityWindowInfo` and `AccessibilityNodeInfo` objects. It reduces the overhead of IPC calls by storing snapshots of the accessibility tree and windows. It actively invalidates or updates the cache based on `AccessibilityEvent`s.

## Architecture
*   **Storage**:
    *   `mWindowCacheByDisplay`: SparseArray mapping Display ID -> (Window ID -> `AccessibilityWindowInfo`).
    *   `mNodeCache`: SparseArray mapping Window ID -> (Node ID -> `AccessibilityNodeInfo`).
*   **Integrity**: Includes a `checkIntegrity()` method (active in debug/eng builds) to ensure the cached tree is consistent (no duplicates, correct parent-child relationships).

## Key Algorithms
*   **`onAccessibilityEvent`**:
    *   Listens for events like `TYPE_VIEW_ACCESSIBILITY_FOCUSED`, `TYPE_WINDOW_CONTENT_CHANGED`, etc.
    *   Invalidates specific nodes or subtrees based on the event type.
    *   For `TYPE_WINDOWS_CHANGED`, it may clear the entire window cache.
*   **`add`**: Caches an `AccessibilityNodeInfo`. It checks for existing nodes and potentially clears subtrees if the new node indicates structure changes (e.g., different parent/children).
*   **`getNode`**: Returns a *copy* of the cached node to prevent clients from recycling the cached instance.

## Java-to-C++ Translation Guide
*   **Locking**: Uses `synchronized(mLock)`. C++ should use `std::mutex` or `std::shared_mutex`.
*   **Data Structures**: `SparseArray` and `LongSparseArray` map efficiently to `std::map` or `std::unordered_map`.
