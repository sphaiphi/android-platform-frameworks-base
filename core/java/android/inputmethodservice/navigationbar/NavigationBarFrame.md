# NavigationBarFrame - Reverse Engineering Documentation

## Executive Summary
`NavigationBarFrame` is the root FrameLayout for the IME navigation bar. It delegates touch events to the `DeadZone` before processing them.

## Detailed Functionality
*   **Dispatch**: Overrides `dispatchTouchEvent` to call `mDeadZone.onTouchEvent`.

## Java-to-C++ Translation Guide
*   **Event Interception**: Standard View dispatch override.
