# MergeCursor - Reverse Engineering Documentation

## Executive Summary
`MergeCursor` presents a view of multiple `Cursor` objects concatenated as a single linear result set. It is useful for combining results from disparate sources (e.g., local DB + network results) into a unified list.

## Architecture Overview
*   **Inheritance**: `AbstractCursor`.
*   **Composition**: Holds an array of `Cursor` objects (`mCursors`).

## Detailed Functionality

### Navigation (`onMove`)
*   **Problem**: Map global position to specific sub-cursor and local position.
*   **Algorithm**:
    *   Iterate `mCursors`.
    *   Keep running `cursorStartPos` (sum of counts seen so far).
    *   If `newPosition < cursorStartPos + current.getCount()`:
        *   Found target cursor.
        *   `mCursor` (current active) = `current`.
        *   `mCursor.moveToPosition(newPosition - cursorStartPos)`.
        *   Break.

### Data Access
*   **Delegation**: All getters (`getString`, etc.) delegate to `mCursor` (the active sub-cursor determined by `onMove`).

### Aggregation
*   `getCount()`: Sum of all sub-cursor counts.
*   `close()`: Closes all sub-cursors.
*   `requery()`: Requeries all sub-cursors. Fails if any fail.

### Observation
*   **DataSetObserver**: Registers a local observer on all sub-cursors. If any changes/invalidates, `MergeCursor` invalidates itself (resets pos to -1).

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `mCursors` | `Cursor[]` | The input cursors. |
| `mCursor` | `Cursor` | The currently active sub-cursor. |
| `mObserver` | `DataSetObserver` | Monitors sub-cursors. |

## Java-to-C++ Translation Guide
*   **Logic**: Pure logic translation.
*   **Optimization**: `onMove` is O(N) where N is number of cursors. Usually N is small (2-3).

## Test Cases
1.  **Boundary**: 2 cursors of size 5. Move to 0 (Cursor A), 4 (Cursor A), 5 (Cursor B), 9 (Cursor B).
2.  **Empty**: MergeCursor with empty sub-cursors. `getCount` should be 0.
3.  **Close**: Closing MergeCursor closes children.
