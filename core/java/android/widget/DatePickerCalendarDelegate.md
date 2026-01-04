# DatePickerCalendarDelegate - Reverse Engineering Documentation

## Executive Summary
`DatePickerCalendarDelegate` is a specific implementation of the `DatePicker` logic that provides a modern, calendar-based user interface (Material Design style). It displays a monthly calendar grid (`DayPickerView`) and a year selector (`YearPickerView`), contrasting with the older "spinner" (Holo) style.

## Architecture Overview
*   **Inheritance**: `DatePicker.AbstractDatePickerDelegate`.
*   **Composition**:
    *   `DayPickerView`: The monthly calendar grid.
    *   `YearPickerView`: The list of years.
    *   `ViewAnimator`: Switches between day and year views.
    *   `ViewGroup mContainer`: The root layout inflated from `R.layout.date_picker_material`.

## Detailed Functionality

### 1. View Management
*   **Views**:
    *   `VIEW_MONTH_DAY` (0): Shows `DayPickerView` (the grid).
    *   `VIEW_YEAR` (1): Shows `YearPickerView` (the list).
*   **Header**: Displays the selected year and month/day. Clicking the year text switches to the year view; clicking the date text switches to the day view.
*   **Accessibility**: uses `ClickActionDelegate` to expose standard click actions.

### 2. Date Logic
*   **State**: Maintains `mCurrentDate`, `mMinDate`, `mMaxDate` using `java.util.Calendar`.
*   **Synchronization**:
    *   When a day is selected (`OnDaySelectedListener`): Updates `mCurrentDate` and switches back to day view.
    *   When a year is selected (`OnYearSelectedListener`): Updates the year, ensures the day is valid (e.g., handles Feb 29 -> Feb 28), and auto-switches back to the day picker.

### 3. Locale & Formatting
*   Uses `icu.text.DateFormat` for robust internationalization.
*   Formats the header strings ("EMMMd" for "Fri, Dec 31", "y" for "2023").
*   Updates on configuration/locale changes.

## Java-to-C++ Translation Guide
*   **Date/Time**: Strongly depends on `icu` libraries. C++ implementation should use ICU or `std::chrono` (with date library).
*   **Layout**: The container layout is complex (header + animator). The C++ equivalent should likely use a layout file or explicit composition.

## Implementation Risks
*   **Date Math**: "Clamping" logic (ensuring date is within min/max, handling leap years when changing years) is subtle and error-prone.
*   **Focus Management**: switching between views requires careful focus restoration (`requestFocus()`).
