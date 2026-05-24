# CalendarView - Reverse Engineering Documentation

## Executive Summary
`CalendarView` is a widget for displaying and selecting dates. It supports two visual modes: **Holo** (legacy) and **Material**. It acts as a facade, delegating all logic to a `CalendarViewDelegate`.

## Architecture Overview
*   **Inheritance**: `FrameLayout` -> `CalendarView`.
*   **Pattern**: Delegate Pattern.
*   **Delegates**:
    *   `CalendarViewLegacyDelegate`: The old-school scrolling list of weeks.
    *   `CalendarViewMaterialDelegate`: The modern `ViewPager`-based month picker.

## Detailed Functionality
*   **Initialization**: Reads attributes (`minDate`, `maxDate`, `weekDayTextAppearance`, etc.) and instantiates the appropriate delegate based on the `calendarViewMode` attribute.
*   **API Forwarding**: All public methods (`setDate`, `getDate`, `setOnDateChangeListener`) forward calls to `mDelegate`.

## Java-to-C++ Translation Guide
*   **Abstraction**: Implement the Delegate interface.
*   **Complexity**: The heavy lifting is in the delegates. You likely only need to implement one (Material) for a modern system.

## Implementation Risks
*   **State Management**: Synchronizing state between the view and the delegate.
