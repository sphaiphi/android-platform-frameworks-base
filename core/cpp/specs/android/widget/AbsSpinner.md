# AbsSpinner - Reverse Engineering Documentation

## Executive Summary
`AbsSpinner` is an abstract base class for spinner-like widgets (e.g., `Gallery`, `Spinner`). It extends `AdapterView` and implements the basic logic for managing a list of items where one item is selected/displayed at a time, often utilizing a recycling mechanism for efficiency.

## Architecture Overview
*   **Inheritance**: `ViewGroup` -> `AdapterView<SpinnerAdapter>` -> `AbsSpinner`.
*   **Role**: Base layout and selection logic for spinner widgets.
*   **Key Components**:
    *   `SpinnerAdapter`: Source of data and views.
    *   `RecycleBin`: Internal inner class (likely distinct from `AbsListView`'s but similar concept) for reusing views.
    *   `mSelection...Padding`: Padding specifically used for positioning the selection.

## Detailed Functionality

### 1. Measurement (`onMeasure`)
*   Measures the selected view to determine the preferred height/width of the spinner.
*   Uses `mRecycleBin` to retrieve a view for measurement purposes without attaching it, or reuses the currently selected view.
*   Sets the dimension based on the child's size plus padding.

### 2. View Recycling
*   **`RecycleBin`**: Stores detached views. When the adapter is asked for a view, `AbsSpinner` looks here first.
*   **`resetList`**: Clears the state and empties the recycler.

### 3. Selection
*   **`setSelection`**: Updates the currently selected item position and requests a layout.
*   **`pointToPosition`**: Maps screen coordinates to the index of the child view at that location.

## Java-to-C++ Translation Guide
*   **Adapter Interface**: Requires an equivalent to `SpinnerAdapter` (extending `Adapter`) in C++.
*   **Layout Pass**: The specific layout logic (how children are arranged) is left to subclasses (`Spinner` vs `Gallery`). C++ implementation should ensure `onMeasure` sets proper dimensions.
*   **Touch Hit Testing**: Implement `pointToPosition` by iterating visible children and checking rect containment.

## Implementation Risks
*   **Measurement Loop**: Calculating size often involves obtaining a view from the adapter. If the adapter is slow or complex, this can impact performance.
*   **Block Layout Requests**: Includes logic (`mBlockLayoutRequests`) to prevent infinite layout loops during selection updates.
