# ArrayAdapter - Reverse Engineering Documentation

## Executive Summary
`ArrayAdapter` is a concrete `BaseAdapter` that backs a list with an array or `List<T>` of arbitrary objects. By default, it expects a layout resource containing a `TextView`, into which it puts the `toString()` result of the objects.

## Architecture Overview
*   **Inheritance**: `BaseAdapter` -> `ArrayAdapter`.
*   **Implements**: `Filterable`.
*   **Data Source**: `List<T> mObjects`.

## Detailed Functionality

### 1. View Generation (`getView`)
*   Inflates `mResource`.
*   Finds the `TextView` (either the root view or specified by `mFieldId`).
*   Sets the text using `item.toString()` or `text.setText(item)` if it's CharSequence.

### 2. Filtering (`ArrayFilter`)
*   Implements a prefix-based filter.
*   **Logic**:
    *   Keeps a copy of original data (`mOriginalValues`).
    *   Iterates through original data, comparing the prefix string to the item's string representation.
    *   Updates `mObjects` with the filtered results and calls `notifyDataSetChanged`.

### 3. Threading
*   **Locking**: Uses `mLock` to synchronize access to the data list during filtering, as filtering happens on a background thread while the UI thread might try to read count/items.

## Java-to-C++ Translation Guide
*   **Templates**: C++ templates are perfect for `ArrayAdapter<T>`.
*   **Concurrency**: Mutex protection for the data container is essential due to the async filtering.

## Implementation Risks
*   **Large Lists**: Filtering a large list is $O(N)$ and involves string allocations.
*   **Layout Inflation**: Inflating views for every item can be slow; recycling (`convertView`) is critical.
