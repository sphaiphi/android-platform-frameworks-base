# CursorTreeAdapter - Reverse Engineering Documentation

## Executive Summary
`CursorTreeAdapter` is an adapter that exposes data from a set of `Cursor`s to an `ExpandableListView`. It manages a main cursor for groups and spawns/caches individual cursors for the children of each group.

## Architecture Overview
*   **Inheritance**: `BaseExpandableListAdapter` -> `CursorTreeAdapter`.
*   **Key Components**:
    *   `MyCursorHelper`: Internal class wrapping a cursor and its observers.
    *   `mGroupCursorHelper`: Manages the group cursor.
    *   `mChildrenCursorHelpers`: `SparseArray` mapping group position to a helper for that group's children.

## Detailed Functionality

### 1. Group/Child Lifecycle
*   **Groups**: Loaded from the main cursor passed in constructor.
*   **Children**:
    *   `getChildrenCursor(Cursor groupCursor)`: Abstract method the subclass implements to return a cursor for a specific group.
    *   The adapter manages these child cursors, deactivating them when the group collapses (`onGroupCollapsed`).

### 2. View Generation
*   `getGroupView` / `getChildView`: Moves the respective cursor to the correct position and calls `newGroupView`/`bindGroupView` etc.

## Java-to-C++ Translation Guide
*   **Caching**: Replicate the `SparseArray` cache for child cursors.
*   **Lazy Loading**: Child cursors are typically fetched on demand.

## Implementation Risks
*   **Cursor Leaks**: Failure to close child cursors when the adapter is destroyed or groups are collapsed.
*   **Performance**: Many open cursors can strain database resources.
