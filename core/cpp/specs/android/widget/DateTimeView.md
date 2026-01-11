# DateTimeView - Reverse Engineering Documentation

## Executive Summary
`DateTimeView` is a specialized `TextView` used primarily in Notifications to display a time stamp that updates automatically (e.g., "now", "5 min ago", or a specific time). It handles relative time formatting and updates itself as time passes.

## Architecture Overview
*   **Inheritance**: `TextView` -> `DateTimeView`.
*   **Role**: Self-updating time display.
*   **Mechanism**: Uses a `ReceiverInfo` thread-local singleton to register a `BroadcastReceiver` for `ACTION_TIME_TICK` (every minute).

## Detailed Functionality

### 1. Smart Updating
*   **`update()`**: Calculates the appropriate display string.
*   **Modes**:
    *   **Time**: Displays HH:MM.
    *   **Date**: Displays Month/Day/Year (if the time is not "today").
    *   **Relative**: "x min ago", etc.
*   **Scheduling**: Calculates `mUpdateTimeMillis` (the next time the text needs to change) and ignores ticks until then to save battery.

### 2. ReceiverInfo
*   Static inner class that manages a single BroadcastReceiver for all DateTimeViews attached to a thread.
*   Prevents registering thousands of receivers if many notifications are visible.

## Java-to-C++ Translation Guide
*   **Time Formatting**: Uses `java.text.DateFormat` and `DateUtils`. Needs C++ equivalent.
*   **Event Loop**: Needs a way to hook into system time tick events.

## Implementation Risks
*   **Battery**: Efficiently handling updates is crucial.
*   **Locale**: Relative time strings need proper pluralization support.
