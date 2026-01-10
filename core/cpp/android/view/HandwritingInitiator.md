# HandwritingInitiator - Reverse Engineering Documentation

## Executive Summary
`HandwritingInitiator` is responsible for detecting stylus movement in "handwritable" areas and automatically triggering the system's handwriting mode. It is used by `ViewRootImpl` to intercept stylus events before they are processed by the regular view hierarchy.

## Architecture Overview
*   **Role**: Stylus-to-Handwriting gesture detector.
*   **Trigger**: Initiates handwriting mode when a stylus moves more than the "handwriting slop" distance.
*   **Integration**: Works closely with `InputMethodManager` (IMM) to route events to the handwriting-enabled IME.

## Detailed Functionality

### 1. Gesture Detection
*   **`onTouchEvent()`**: Analyzes stylus `MotionEvent` streams.
*   **Handwriting Slop**: Prevents accidental triggers during taps or long-clicks.
*   **Timeout**: If no movement occurs within a specific window, handwriting is aborted.

### 2. Area Tracking
*   **`HandwritingAreaTracker`**: Keeps a list of all views that have declared themselves handwritable.
*   **Coordinate Mapping**: Maps view-local handwriting areas into window-space for hit-testing against stylus events.

### 3. Delegation
*   **`prepareDelegation()`**: Handles cases where one view acts as a "delegator" for another (e.g., a non-editable label triggering handwriting for an adjacent text field).

## Java-to-C++ Translation Guide
*   **Event Pipeline**: In C++, this component should sit between the `InputReceiver` and the `View` tree.
*   **Hit-Testing**: Requires efficient intersection checks between stylus points and tracked rectangles.

## Implementation Risks
*   **Flicker**: Incorrectly cancelling a touch event stream when switching to handwriting mode can cause UI artifacts.
*   **Privacy**: Handwriting initiation involves tracking stylus motion across windows; ensure it respects window focus and visibility rules.
