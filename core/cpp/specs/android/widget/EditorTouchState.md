# EditorTouchState - Reverse Engineering Documentation

## Executive Summary
`EditorTouchState` is a helper class for `Editor` that tracks touch events to detect gestures like double-tap, triple-tap, and drag initiation.

## Architecture Overview
*   **Role**: Gesture Detector / State Machine.

## Detailed Functionality
*   **Multi-tap**: Tracks time and distance between clicks to detect MultiTap status (`FIRST_TAP`, `DOUBLE_TAP`, `TRIPLE_CLICK`).
*   **Drag Detection**: Calculates distance squared vs touch slop to determine if a move event is a drag.
*   **Drag Direction**: Calculates the angle of the drag (XY ratio) to determine if it's vertical (scroll) or horizontal (selection drag).

## Java-to-C++ Translation Guide
*   **GestureDetector**: Standard gesture logic.

## Implementation Risks
*   None.
