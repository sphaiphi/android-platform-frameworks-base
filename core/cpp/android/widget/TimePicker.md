# TimePicker - Reverse Engineering Documentation

## Executive Summary
`TimePicker` is a widget for selecting the time of day. Like `DatePicker`, it uses a delegate pattern to support different visual styles (Spinner vs Clock).

## Architecture Overview
*   **Inheritance**: `FrameLayout` -> `TimePicker`.
*   **Modes**:
    *   `MODE_SPINNER` (1): Holo style (scrolling wheels).
    *   `MODE_CLOCK` (2): Material style (radial clock face).
*   **Delegates**: `TimePickerSpinnerDelegate`, `TimePickerClockDelegate`.

## Detailed Functionality
*   **State**: Tracks hour (0-23) and minute (0-59).
*   **24-Hour Mode**: Toggles between 12h (AM/PM) and 24h formats.
*   **Autofill**: Supports autofilling time values.

## Java-to-C++ Translation Guide
*   **Composition**: Main container class.
*   **Delegation**: Forward all calls to the active delegate.

## Implementation Risks
*   **Validation**: Input validation.
