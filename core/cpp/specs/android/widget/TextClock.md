# TextClock - Reverse Engineering Documentation

## Executive Summary
`TextClock` is a specialized `TextView` that displays the current date and/or time formatted as a string. It automatically updates itself (ticks) and respects the system's 12/24-hour format preference.

## Architecture Overview
*   **Inheritance**: `TextView` -> `TextClock`.
*   **Role**: Clock Display.
*   **Dependencies**: `Calendar`, `DateFormat` (Android), `SimpleDateFormat` (implied).

## Detailed Functionality

### 1. Formatting
*   **Modes**: Maintains two format strings: `mFormat12` (for 12-hour mode) and `mFormat24` (for 24-hour mode).
*   **Selection**: Uses `DateFormat.is24HourFormat` (or user preference if `mShowCurrentUserTime` is set) to choose which format to apply.
*   **Skeleton**: If no format is provided, it derives a best-match format from the locale using `DateTimePatternGenerator` (e.g., "hm" -> "h:mm a").

### 2. Ticking
*   **Ticker**: A `Runnable` that reposts itself (`postDelayed`).
*   **Interval**:
    *   If the format contains seconds: ticks every second.
    *   Otherwise: ticks every minute (aligned to the start of the minute).
*   **Updates**: Calls `setText` with the formatted time.

### 3. Events
*   **BroadcastReceiver**: Listens for `ACTION_TIME_TICK`, `ACTION_TIME_CHANGED`, `ACTION_TIMEZONE_CHANGED`.
*   **ContentObserver**: Listens for `Settings.System.TIME_12_24` changes.

## Java-to-C++ Translation Guide
*   **Time**: Use `std::chrono` and `std::put_time` (or ICU).
*   **Looper**: Needs a delayed execution mechanism for the ticker.
*   **System Settings**: Needs to observe system clock preferences.

## Implementation Risks
*   **Battery**: Aggressive ticking (seconds) prevents CPU sleep if the view is visible. Ensure it stops ticking when detached or invisible (`onVisibilityAggregated`).
