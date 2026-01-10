# AutoCompleteTextView - Reverse Engineering Documentation

## Executive Summary
`AutoCompleteTextView` is an editable text view that shows completion suggestions automatically while the user types. The suggestions are displayed in a `ListPopupWindow`.

## Architecture Overview
*   **Inheritance**: `EditText` -> `AutoCompleteTextView`.
*   **Key Components**:
    *   `ListPopupWindow`: The dropdown window.
    *   `ListAdapter`: Source of suggestions.
    *   `Filter`: Logic to constrain suggestions.
    *   `Validator`: Optional input validation.

## Detailed Functionality

### 1. Typing & Filtering
*   **`TextWatcher`**: Monitors text changes.
*   **`performFiltering`**: When text length > `mThreshold`, calls `mFilter.filter()`.
*   **Async Result**: When filtering completes, `onFilterComplete` updates the popup.

### 2. Dropdown Management
*   **Showing**: Anchors the popup to the TextView.
*   **Selection**: Handles clicks on the list (`performCompletion`), replacing the text content.

### 3. Validation
*   **`performValidation`**: Called when the view loses focus. If the text isn't in the list (or valid per `mValidator`), it can fix it or clear it.

## Java-to-C++ Translation Guide
*   **Popup**: Relies on the `ListPopupWindow` implementation.
*   **Filtering**: Needs a background thread mechanism for filter queries.

## Implementation Risks
*   **Z-Ordering**: The popup is a separate window; handling focus transitions between the edit text and the popup list is tricky.
*   **Input Method**: Interaction with the soft keyboard (IME) needs care so the dropdown doesn't obscure it or get hidden incorrectly.
