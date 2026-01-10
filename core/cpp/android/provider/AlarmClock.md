# AlarmClock - Reverse Engineering Documentation

## Executive Summary
`AlarmClock` is a utility class defining Intents for interacting with alarm clock applications. It allows apps to set alarms, timers, snooze alarms, and show lists of alarms or timers without needing to implement their own alarm UI.

## Architecture Overview
- **Type**: Intent Contract Class.
- **Role**: Defines `Intent` actions and extras for the `AlarmClock` provider.

## Detailed Functionality
-   **Actions**:
    -   `ACTION_SET_ALARM`: Sets an alarm. Can specify time, message, ringtone, skip UI, etc.
    -   `ACTION_SET_TIMER`: Sets a timer. Can specify length, message, skip UI.
    -   `ACTION_DISMISS_ALARM`: Dismisses an alarm. Can search by time, content, or "next".
    -   `ACTION_DISMISS_TIMER`: Dismisses a timer.
    -   `ACTION_SNOOZE_ALARM`: Snoozes the currently ringing alarm.
    -   `ACTION_SHOW_ALARMS`: Opens the alarms list.
    -   `ACTION_SHOW_TIMERS`: Opens the timers list.
-   **Extras**: Keys for passing parameters like hour, minutes, message, ringtone, etc.

## Data Model
-   **Constants**: Action strings and Extra keys.

## API Reference
-   `ACTION_SET_ALARM`, `ACTION_SET_TIMER`, `ACTION_DISMISS_ALARM`, etc.
-   `EXTRA_HOUR`, `EXTRA_MINUTES`, `EXTRA_MESSAGE`, `EXTRA_RINGTONE`, etc.

## Java-to-C++ Translation Guide
-   **Intents**: Map these constants to C++ strings for constructing Intents (if using a C++ Intent wrapper).
