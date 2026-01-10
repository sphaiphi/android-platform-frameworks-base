# TextInputTimePickerView - Reverse Engineering Documentation

## Executive Summary
`TextInputTimePickerView` is the internal view used by `TimePicker` when in "keyboard" input mode (as opposed to the radial clock face). It allows typing the hour and minute directly.

## Architecture Overview
*   **Inheritance**: `RelativeLayout` -> `TextInputTimePickerView`.
*   **Role**: Internal Input Interface.
*   **Components**:
    *   `EditText`: Hour and Minute fields.
    *   `Spinner`: AM/PM selector.

## Detailed Functionality

### 1. Input Handling
*   **Validation**: Validates input ranges (0-23 or 1-12, 0-59) via `TextWatcher` and `InputFilter`.
*   **Auto-Advance**: If the user types a valid hour (e.g., "5" or "12"), it may auto-focus the minute field (implied logic, possibly in the listener).
*   **Error**: Shows an error label if input is out of bounds.

### 2. Data Flow
*   **Listener**: Notifies `OnValueTypedListener` when valid values are entered.
*   **Update**: `updateTextInputValues` sets the text fields from the external state (e.g., if updated by the radial picker or API).

## Java-to-C++ Translation Guide
*   **Composite View**: Standard layout with child widgets.
*   **Input Mask**: Requires integer-only input fields with range checking.

## Implementation Risks
*   **Locale**: Hour format (starting at 0 vs 1) depends on locale and 24h settings.
