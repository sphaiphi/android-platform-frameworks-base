# DayPickerViewPager - Reverse Engineering Documentation

## Executive Summary
`DayPickerViewPager` is a specialized `ViewPager` used by `DayPickerView`. It overrides `onMeasure` to handle the specific sizing requirements of the date picker (wrapping content height while respecting match parent constraints).

## Architecture Overview
*   **Inheritance**: `ViewPager` -> `DayPickerViewPager`.

## Detailed Functionality
*   **`onMeasure`**:
    *   Iterates children to find the maximum height required.
    *   Resolves size against `MeasureSpec`.
    *   Populates the ViewPager.

## Java-to-C++ Translation Guide
*   **Custom ViewPager**: Extend the standard paging component.

## Implementation Risks
*   None.
