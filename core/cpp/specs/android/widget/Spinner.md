# Spinner - Reverse Engineering Documentation

## Executive Summary
`Spinner` is a view that displays a single selected value from a set. Clicking it opens a popup (Dialog or Dropdown) to allow selection. It is the Android equivalent of a "Combo Box".

## Architecture Overview
*   **Inheritance**: `AbsSpinner` -> `Spinner`.
*   **Modes**: `MODE_DIALOG` (0) or `MODE_DROPDOWN` (1).
*   **Strategy**: `SpinnerPopup` interface abstracts the UI implementation (Dialog vs Popup Window).

## Detailed Functionality

### 1. Popup Management
*   **`DropdownPopup`**: Extends `ListPopupWindow`. Anchors to the Spinner.
*   **`DialogPopup`**: Wraps an `AlertDialog`.
*   **Forwarding**: Uses `ForwardingListener` to support drag-to-open gesture for the dropdown.

### 2. Adapter (`DropDownAdapter`)
*   Wraps the user's `SpinnerAdapter`.
*   The `Spinner` itself displays the *selected* view (using `getView`).
*   The Popup displays the *list* of views (using `getDropDownView`). The wrapper bridges this.

### 3. Layout & Measurement
*   **`measureContentWidth`**: Calculates the widest item in the adapter to size the dropdown correctly.
*   **`onLayout`**: Positions the selected view.

## Java-to-C++ Translation Guide
*   **Strategy Pattern**: Use the `SpinnerPopup` interface abstraction.
*   **Popups**: Requires window management.

## Implementation Risks
*   **Width Calculation**: Measuring every item in the adapter to find the max width is expensive (`MAX_ITEMS_MEASURED` limit).
