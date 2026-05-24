# InputEventAssigner - Reverse Engineering Documentation

## Executive Summary
`InputEventAssigner` is a utility used to associate input events with specific display frames. It ensures that the first event of a gesture (ACTION_DOWN) is prioritized for the next VSync, and subsequently tracks movement events to maintain smooth synchronization between input and rendering.

## Architecture Overview
*   **Role**: Input-to-Frame synchronization logic.
*   **Mechanism**: Tracks whether a "Down" event is pending processing and returns the appropriate event ID for the current frame.

## Detailed Functionality
*   **`processEvent(InputEvent)`**: Analyzes a motion event and returns the ID that should be attributed to the current frame. For touch gestures, it ensures the "Down" ID is used until the first frame is processed.
*   **`notifyFrameProcessed()`**: Signals that the "Down" event has been handled and the assigner can switch to using the IDs of newer events.

## Java-to-C++ Translation Guide
*   **State Management**: In C++, this can be a simple state machine with a few integers.
*   **Constants**: Uses `INVALID_INPUT_EVENT_ID` (-1) for resetting state.

## Implementation Risks
*   **Sync Accuracy**: If `notifyFrameProcessed` is called incorrectly, input latency metrics (jank tracking) will be inaccurate as events will be attributed to the wrong frames.
