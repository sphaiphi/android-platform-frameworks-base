# GestureDetector - Reverse Engineering Documentation

## Executive Summary
`GestureDetector` is a utility class that analyzes a stream of `MotionEvent`s to identify common touch gestures like Taps, Double-Taps, Scrolls, Flings, and Long Presses. It simplifies touch interaction by providing a callback-based interface (`OnGestureListener`).

## Architecture Overview
*   **Role**: Gesture recognition engine.
*   **Logic**: Uses a state machine and internal timers (via `Handler`) to distinguish between stationary holds (Long Press) and movement (Scroll/Fling).
*   **Threading**: Callbacks occur on the thread that created the detector (requires a `Looper`).

## Detailed Functionality

### 1. Recognition Logic
*   **`onDown()`**: Triggered immediately on first contact.
*   **`onScroll()`**: Triggered when movement exceeds the `touchSlop`.
*   **`onFling()`**: Triggered on `ACTION_UP` if the velocity exceeds the threshold.
*   **`onLongPress()`**: Triggered via a delayed message if no movement or release occurs within the timeout.

### 2. Multi-Tap Support
*   **`OnDoubleTapListener`**: Specifically tracks two consecutive taps within a time window and distance threshold.

### 3. Velocity Tracking
*   Uses `VelocityTracker` internally to calculate the speed of movements for fling detection.

## Java-to-C++ Translation Guide
*   **Event Handling**: In C++, this can be implemented as a stateful processor that accepts `android::MotionEvent`.
*   **Timers**: Requires a `Looper` or similar event loop to handle delayed gesture detection (like Long Press).
*   **Thresholds**: Fetch constants like `touchSlop` from a C++ `ViewConfiguration` equivalent.

## Implementation Risks
*   **Consistency**: The detector depends on receiving a complete stream of events (Down -> Move -> Up). Dropping events will break the state machine.
*   **Conflict**: If multiple detectors are used on the same event stream, they may "fight" for consumption.
