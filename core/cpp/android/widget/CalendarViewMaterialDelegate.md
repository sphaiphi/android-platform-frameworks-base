# CalendarViewMaterialDelegate - Reverse Engineering Documentation

## Executive Summary
`CalendarViewMaterialDelegate` implements the "Material" style calendar. It simplifies the structure compared to the legacy delegate by using a `DayPickerView`, which internally uses a `ViewPager`-like approach to swipe between months.

## Architecture Overview
*   **Inheritance**: `AbstractCalendarViewDelegate`.
*   **Key Component**: `DayPickerView`.

## Detailed Functionality
*   **Composition**: It instantiates and adds a `DayPickerView` to the `CalendarView`.
*   **Forwarding**: Maps `CalendarView` attributes (min/max date, text appearance) to setters on `DayPickerView`.
*   **Events**: Listens to `DayPickerView.OnDaySelectedListener` and forwards to `CalendarView.OnDateChangeListener`.

## Java-to-C++ Translation Guide
*   **Modularization**: Implement `DayPickerView` first. This delegate is mostly glue code.

## Implementation Risks
*   None relative to this class; complexity lies in `DayPickerView`.
