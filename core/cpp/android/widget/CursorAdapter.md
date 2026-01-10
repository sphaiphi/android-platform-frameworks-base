# CursorAdapter - Reverse Engineering Documentation

## Executive Summary
`CursorAdapter` is an adapter that exposes data from a `Cursor` to a `ListView`. It handles the details of moving the cursor to the correct position for each row and observing data changes to auto-refresh the list.

## Architecture Overview
*   **Inheritance**: `BaseAdapter` -> `CursorAdapter`.
*   **Key Components**:
    *   `mCursor`: The database cursor.
    *   `mRowIDColumn`: Index of the "_id" column (required for stable IDs).
    *   `ChangeObserver`: Listens for content changes.
    *   `DataSetObserver`: Listens for invalidation.

## Detailed Functionality

### 1. Data Binding (`getView`)
*   Checks if `mDataValid`.
*   Moves cursor: `mCursor.moveToPosition(position)`.
*   **`newView`**: Abstract method to inflate a new view.
*   **`bindView`**: Abstract method to populate the view with data from the current cursor row.

### 2. Cursor Management
*   **`swapCursor`**: Replaces the current cursor with a new one, registering/unregistering observers. Returns the old cursor (does not close it).
*   **`changeCursor`**: Like swap, but closes the old cursor.

### 3. Filtering (`CursorFilter`)
*   Implements `Filterable`.
*   Delegates filtering to a `FilterQueryProvider` or abstract `runQueryOnBackgroundThread`.
*   Updates the adapter with the new cursor returned by the query.

## Java-to-C++ Translation Guide
*   **Data Abstraction**: Needs a C++ abstraction for `Cursor` (row-based random access to database results).
*   **Lifecycle**: Managing the cursor lifecycle (close/release) is critical to prevent leaks.

## Implementation Risks
*   **Performance**: Cursor operations on the UI thread (like `getView` moving the cursor) can be slow if the window is large.
*   **Stale Data**: Handling the gap between a data change notification and the arrival of the new cursor.
