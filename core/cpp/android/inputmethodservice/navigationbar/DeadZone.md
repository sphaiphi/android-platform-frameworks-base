# DeadZone - Reverse Engineering Documentation

## Executive Summary
`DeadZone` implements logic to ignore accidental touches at the edges of the navigation bar (e.g., overshooting the spacebar). It defines a region that consumes touches ("eats" them) based on time since last activity.

## Detailed Functionality
*   **Dynamic Sizing**: Size of dead zone decays over time (`getSize(now)`). Expands on interaction, shrinks when idle.
*   **Hit Testing**: `onTouchEvent` checks if touch falls within the calculated dead zone rect.
*   **Visual Debugging**: Can flash (`onDraw`) to show the dead zone area.

## Java-to-C++ Translation Guide
*   **Input Filter**: This logic belongs in the input event dispatch pipeline.
*   **Math**: Lerp functions for decay.
