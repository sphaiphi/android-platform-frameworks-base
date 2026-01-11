# DayPickerPagerAdapter - Reverse Engineering Documentation

## Executive Summary
`DayPickerPagerAdapter` is an adapter for `ViewPager` that displays a list of months (`SimpleMonthView`). It is used by the Material `DatePicker`.

## Architecture Overview
*   **Inheritance**: `PagerAdapter`.
*   **Content**: Pages are `SimpleMonthView`s.

## Detailed Functionality
*   **Range**: Calculates the total number of months between `mMinDate` and `mMaxDate`.
*   **Instantiation**: Creates a `SimpleMonthView`, sets its params (month, year, selected day, enabled range), and adds it to the container.
*   **Mapping**: Maps a position index to a specific Month/Year.

## Java-to-C++ Translation Guide
*   **ViewPager Adapter**: Requires a C++ `ViewPager` equivalent.

## Implementation Risks
*   None.
