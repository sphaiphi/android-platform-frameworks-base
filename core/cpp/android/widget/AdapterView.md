# AdapterView - Reverse Engineering Documentation

## Executive Summary
`AdapterView` is an abstract generic subclass of `ViewGroup` whose children are determined by an `Adapter`. It creates the foundation for `ListView`, `GridView`, and `Spinner`. It handles the logic for binding data to views, item selection, and click events.

## Architecture Overview
*   **Inheritance**: `ViewGroup` -> `AdapterView<T extends Adapter>`.
*   **Generics**: Parameterized by the type of Adapter it uses.
*   **Role**: Base class for data-driven views.

## Detailed Functionality

### 1. Data Observer
*   Registers a `DataSetObserver` on the adapter.
*   **`mDataChanged`**: Flag set when data changes. Triggers layout.
*   **`mOldItemCount`** vs `mItemCount`: Tracks size changes to handle state restoration or selection clamping.

### 2. Selection Management
*   **`mSelectedPosition`**: Index of the currently selected item (for D-pad/trackball navigation).
*   **`mNextSelectedPosition`**: Pending selection update.
*   **`selectionChanged()`**: Callback hook for subclasses.
*   **`findSyncPosition()`**: Logic to attempt to persist selection across data updates (e.g., finding the same item ID after a refresh).

### 3. Empty View
*   **`setEmptyView(View)`**: Automatically hides the `AdapterView` and shows the `EmptyView` when the adapter count is 0.

### 4. Click Listeners
*   `OnItemClickListener`: Fires when an item is clicked.
*   `OnItemLongClickListener`: Fires on long press.
*   `OnItemSelectedListener`: Fires on selection change (focus).

## Java-to-C++ Translation Guide
*   **Templating**: C++ templates are a natural fit for `AdapterView<T>`.
*   **Observer Pattern**: Crucial for the Adapter-View communication.
*   **Accessibility**: Contains significant accessibility logic (`onInitializeAccessibilityNodeInfo`) which maps data indices to UI accessibility collections.

## Implementation Risks
*   **State Sync**: Keeping the view state (scroll position, selection) synchronized with the data state (which might change asynchronously) is the hardest part. The `findSyncPosition` logic is complex.
*   **Layout Loops**: Modifying data during layout can cause infinite loops.
