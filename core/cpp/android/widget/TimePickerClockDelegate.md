# TimePickerClockDelegate - Reverse Engineering Documentation

## Executive Summary
`TimePickerClockDelegate` implements the Material Design "Clock" style time picker. It features a large radial clock face (`RadialTimePickerView`) for selecting hours and minutes, along with a digital display header and AM/PM selector.

## Architecture Overview
*   **Inheritance**: `TimePicker.AbstractTimePickerDelegate`.
*   **Components**:
    *   `RadialTimePickerView`: The clock face.
    *   `NumericTextView`: Hour/Minute digital displays (clickable to switch modes).
    *   `RadioButton`: AM/PM selector.
    *   `TextInputTimePickerView`: Keyboard input mode (hidden by default).

## Detailed Functionality

### 1. Radial Picker Interaction
*   **Hour/Minute Switch**: Clicking the hour text switches the radial view to hour mode; clicking minute text switches to minute mode.
*   **Auto-Advance**: After selecting an hour, it automatically transitions to minute selection.
*   **Values**: Updates internal state and UI text on selection.

### 2. Input Mode Toggle
*   A button toggles between the Radial Picker and the `TextInputTimePickerView` (keyboard entry).

### 3. Formatting
*   **Locale**: Formats hour/minute strings based on locale (leading zeros, etc.).
*   **AM/PM**: Positions AM/PM controls based on locale layout (start/end/top/bottom).

## Java-to-C++ Translation Guide
*   **State Machine**: Managing the "Hour Mode" vs "Minute Mode" state.
*   **Touch Handling**: `NearestTouchDelegate` expands touch areas for small targets.

## Implementation Risks
*   **Layout**: The header layout (Hour : Minute AM/PM) varies significantly by locale and 12/24 mode.
