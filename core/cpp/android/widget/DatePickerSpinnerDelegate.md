# DatePickerSpinnerDelegate - Reverse Engineering Documentation

## Executive Summary
`DatePickerSpinnerDelegate` implements the "Spinner" (Holo) style date picker. It composes three `NumberPicker` widgets (Day, Month, Year) and optionally a `CalendarView`.

## Architecture Overview
*   **Inheritance**: `AbstractDatePickerDelegate`.
*   **Components**:
    *   `mDaySpinner`, `mMonthSpinner`, `mYearSpinner`: `NumberPicker`s.
    *   `mCalendarView`: Optional side-view.

## Detailed Functionality

### 1. Spinner Configuration
*   **Ordering**: Determines the order of spinners (D-M-Y, M-D-Y, Y-M-D) based on the user's locale date format (`DateFormat.getDateFormatOrder`).
*   **Month Names**: Populates the month spinner with localized short month names.

### 2. Date Logic
*   **Update**: When one spinner changes, it updates the internal `Calendar`.
*   **Constraints**: Adjusts min/max values of spinners dynamically (e.g., max day changes from 31 to 30 or 28 based on month/year).
*   **Consistency**: Syncs the `CalendarView` if visible.

## Java-to-C++ Translation Guide
*   **Locale**: Critical dependency on locale data for date ordering and month names.
*   **Synchronization**: Updating one spinner often requires updating the bounds of another (e.g., changing month to Feb limits day spinner to 28/29).

## Implementation Risks
*   **Leap Years**: Correctly handling Feb 29.
