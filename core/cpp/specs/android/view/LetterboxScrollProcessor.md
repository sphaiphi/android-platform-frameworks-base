# LetterboxScrollProcessor - Reverse Engineering Documentation

## Executive Summary
`LetterboxScrollProcessor` is an internal utility that enables scrolling gestures to work even when they start in the "letterbox" area (the black bars around an app). it detects scroll gestures outside the app's bounds and forwards them to the app's view hierarchy by translating the coordinates.

## Architecture Overview
*   **Role**: Letterbox-to-App input bridge.
*   **Mechanism**: Uses a `GestureDetector` to identify when a touch in the letterbox area is intended to be a scroll.
*   **State Machine**:
    1.  `AWAITING_GESTURE_START`: Normal state.
    2.  `GESTURE_STARTED_OUTSIDE_APP`: Tracking touch in the black bars.
    3.  `SCROLLING_STARTED_OUTSIDE_APP`: Firing synthetic events to the app.

## Detailed Functionality

### 1. Coordinate Translation
*   **`applyOffset()`**: Calculates the horizontal and vertical distance from the letterbox edge to the app boundary and offsets the `MotionEvent` accordingly.

### 2. Event Injection
*   When a scroll is detected, it obtains the original `ACTION_DOWN` event, translates it, and injects it into the app's event stream followed by the `ACTION_MOVE` events.

## Java-to-C++ Translation Guide
*   **Logic**: Primarily coordinate math and state transitions.
*   **Event Handling**: In C++, this component should wrap the `InputReceiver` logic for letterboxed windows.

## Implementation Risks
*   **Coordinate Systems**: Mismatch between "Window Space" (used for event dispatch) and "Activity Bounds" (used for offset calculation) can lead to broken hit-testing.
*   **Gesture Confusion**: Must carefully distinguish between a scroll and a navigation gesture (like the back swipe) starting near the screen edge.
