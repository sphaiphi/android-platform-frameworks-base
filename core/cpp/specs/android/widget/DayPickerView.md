# DayPickerView - Reverse Engineering Documentation

## Executive Summary
`DayPickerView` is a compound view containing a `ViewPager` (displaying months) and "Previous"/"Next" arrow buttons. It allows selecting a specific day.

## Architecture Overview
*   **Inheritance**: `ViewGroup` -> `DayPickerView`.
*   **Components**:
    *   `ViewPager`: The scrollable area.
    *   `ImageButton`: Prev/Next navigation.
    *   `DayPickerPagerAdapter`: The adapter.

## Detailed Functionality
*   **Navigation**: Clicking arrows changes the ViewPager current item.
*   **Layout**: Manually lays out the buttons on top of the ViewPager header (the month name).
*   **State**: Tracks current date, min/max date.

## Java-to-C++ Translation Guide
*   **Layout Logic**: The `onLayout` method manually positions the arrow buttons to align with the month header text of the underlying `SimpleMonthView`. This requires knowledge of the `SimpleMonthView`'s internal metrics (padding, header height).

## Implementation Risks
*   **Coupling**: High coupling with `SimpleMonthView` layout details.
