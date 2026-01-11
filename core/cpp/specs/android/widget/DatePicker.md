# DatePicker - Reverse Engineering Documentation

## Executive Summary
`DatePicker` is a widget for selecting a date (year, month, day). Like `CalendarView`, it delegates its implementation to a `DatePickerDelegate` to support different visual styles (Spinner vs Calendar).

## Architecture Overview
*   **Inheritance**: `FrameLayout` -> `DatePicker`.
*   **Delegate Pattern**:
    *   `DatePickerSpinnerDelegate`: Uses `NumberPicker`s (scrolling wheels) for day, month, year. (Holo style).
    *   `DatePickerCalendarDelegate`: Uses a header and a `DayPickerView` (calendar grid). (Material style).

## Detailed Functionality
*   **Modes**:
    *   `MODE_SPINNER` (1).
    *   `MODE_CALENDAR` (2).
*   **Attributes**: `startYear`, `endYear`, `minDate`, `maxDate`.
*   **Validation**: Can validate input when used in dialogs.

## Java-to-C++ Translation Guide
*   **Composition**: It's a container.
*   **Logic**: Mostly configuration forwarding.

## Implementation Risks
*   **Locale**: Month names and order (D-M-Y vs M-D-Y) vary by locale.
