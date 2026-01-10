# DatePickerController - Reverse Engineering Documentation

## Executive Summary
`DatePickerController` is a package-private interface used to communicate between the `DatePickerCalendarDelegate` and its sub-components (like `YearPickerView` or `DayPickerView`). It allows these components to request vibration, notify date changes, or query the currently selected date.

## Architecture Overview
*   **Type**: Interface.
*   **Methods**:
    *   `onYearSelected(int)`
    *   `registerOnDateChangedListener`
    *   `getSelectedDay`
    *   `tryVibrate`

## Java-to-C++ Translation Guide
*   **Interface**: Pure virtual abstract class.

## Implementation Risks
*   None.
