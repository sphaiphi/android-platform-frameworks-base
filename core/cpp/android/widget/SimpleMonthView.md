# SimpleMonthView - Reverse Engineering Documentation

## Executive Summary
`SimpleMonthView` is a custom view that renders a single month grid for the material-styled `DatePicker`. It handles drawing the month name, day-of-week headers, and the grid of day numbers. It supports selection, highlighting, and accessibility.

## Architecture Overview
*   **Inheritance**: `View` -> `SimpleMonthView`.
*   **Role**: Grid Renderer.
*   **Accessibility**: Uses `ExploreByTouchHelper` (`MonthViewTouchHelper`) to expose individual days as virtual views.

## Detailed Functionality

### 1. Drawing (`onDraw`)
*   **Month Label**: Draws the month and year centered at the top.
*   **Day Headers**: Draws M, T, W, T, F, S, S row.
*   **Days**: Iterates from 1 to `mDaysInMonth`.
    *   Calculates row/column based on `mWeekStart` and locale (RTL).
    *   Draws circle for selected/today state.
    *   Draws text numbers.

### 2. Interaction
*   **Touch**: `onTouchEvent` maps (x, y) coordinates to a specific day using grid math.
*   **Focus**: Supports keyboard navigation (arrow keys) moving focus between days.
*   **Click**: Triggers `OnDayClickListener`.

### 3. Sizing
*   `onMeasure`: Calculates height based on the number of weeks (rows) needed for the specific month.

## Java-to-C++ Translation Guide
*   **Canvas API**: Relies on `drawText` and `drawCircle`.
*   **Text Layout**: Requires measuring text height/ascent/descent to vertically center numbers.
*   **Calendar Math**: Uses `java.util.Calendar` heavily. Port to `std::chrono` or similar.

## Implementation Risks
*   **RTL**: The grid calculation logic has specific branches for RTL layouts (`isLayoutRtl()`).
*   **Accessibility**: Implementing the virtual view hierarchy is complex but necessary for screen readers.
