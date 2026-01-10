# YearPickerView - Reverse Engineering Documentation

## Executive Summary
`YearPickerView` is a `ListView` that displays a range of years. It is used by `DatePickerCalendarDelegate`.

## Architecture Overview
*   **Inheritance**: `ListView` -> `YearPickerView`.
*   **Adapter**: `YearAdapter` (Internal).

## Detailed Functionality
*   **Layout**: Simple list of TextViews.
*   **Selection**: Centers the selected year in the list using `setSelectionFromTop`.

## Java-to-C++ Translation Guide
*   **List**: Use a standard list component.

## Implementation Risks
*   None.
