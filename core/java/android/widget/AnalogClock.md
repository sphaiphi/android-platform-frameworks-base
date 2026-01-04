# AnalogClock - Reverse Engineering Documentation

## Executive Summary
`AnalogClock` is a widget that displays a dial with hour, minute, and optional second hands. It updates automatically based on the system time and supports time zones.

## Architecture Overview
*   **Inheritance**: `View` -> `AnalogClock`.
*   **Rendering**: Custom `onDraw` using `Canvas`.
*   **Timing**: Uses a `Runnable` (`mTick`) posted to the handler or a `BroadcastReceiver` for `ACTION_TIME_TICK`.

## Detailed Functionality

### 1. Drawing
*   Draws the `mDial` drawable.
*   Rotates the canvas and draws `mHourHand`.
    *   Rotation = `(hours + minutes/60) * 30` degrees.
*   Rotates the canvas and draws `mMinuteHand`.
    *   Rotation = `minutes * 6` degrees.
*   If enabled, rotates and draws `mSecondHand`.

### 2. Updates
*   **Receiver**: Listens for `ACTION_TIME_TICK`, `ACTION_TIME_CHANGED`, `ACTION_TIMEZONE_CHANGED`.
*   **Seconds Hand**: If a second hand is present, it uses `postDelayed` to update every second (or faster based on FPS) instead of relying solely on the minute-tick broadcast.

### 3. Time Zone
*   Supports displaying time for a specific `ZoneId`.

## Java-to-C++ Translation Guide
*   **Graphics**: Standard 2D rendering (translation, rotation, drawing bitmaps/vectors).
*   **Time**: Use `std::chrono` or platform time APIs.

## Implementation Risks
*   **Battery**: If the second hand is enabled, the view invalidates 60 times a second (or more), which prevents the display from idling.
