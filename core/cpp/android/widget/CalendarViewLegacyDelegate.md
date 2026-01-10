# CalendarViewLegacyDelegate - Reverse Engineering Documentation

## Executive Summary
`CalendarViewLegacyDelegate` implements the "Holo" style calendar. It uses a `ListView` (`mListView`) where each item is a `WeekView` (a custom view drawing 7 days). It supports vertical scrolling through weeks.

## Architecture Overview
*   **Inheritance**: `AbstractCalendarViewDelegate`.
*   **Components**:
    *   `WeeksAdapter`: Populates the ListView.
    *   `WeekView`: Custom `View` that draws one week of dates using `Canvas`.
    *   `mDayNamesHeader`: A row of TextViews for "Sun", "Mon", etc.

## Detailed Functionality

### 1. WeekView Drawing
*   Draws the background for selected week.
*   Draws day numbers.
*   Draws separator lines.
*   Calculates touch targets to detect which day was tapped.

### 2. Scrolling & Selection
*   **`goTo`**: Smoothly scrolls the ListView to the specific week.
*   **Friction**: Adjusts ListView friction for a specific feel.
*   **Month Name**: Updates a `TextView` (`mMonthName`) as the user scrolls to indicate the current month in focus.

## Java-to-C++ Translation Guide
*   **Custom Drawing**: Port `WeekView.onDraw`.
*   **List**: Use a virtualized list component.

## Implementation Risks
*   **Performance**: `WeekView` drawing must be efficient.
*   **Complexity**: This delegate is quite complex due to the manual drawing and touch handling within the list items.
