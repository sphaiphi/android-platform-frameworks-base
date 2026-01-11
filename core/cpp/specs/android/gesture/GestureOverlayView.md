# GestureOverlayView - Reverse Engineering Documentation

## Executive Summary
`GestureOverlayView` is a transparent UI view (`FrameLayout`) that overlays other widgets to capture user gestures. It visualizes the gesture as it is drawn and dispatches events to listeners.

## Architecture Overview
- **Inheritance**: Extends `FrameLayout`.
- **Event Handling**: Intercepts touch events (`dispatchTouchEvent`).
- **Rendering**: Draws the current gesture path on a `Canvas`.
- **Fading**: Implements a fading mechanism (`FadeOutRunnable`) to clear gestures after a timeout.

## Detailed Functionality

### Touch Processing
- **ACTION_DOWN**: Starts a new stroke/gesture.
- **ACTION_MOVE**: Updates the current stroke, smooths the path (Bezier curves), and invalidates the dirty region.
- **ACTION_UP**: Completes the gesture and triggers recognition/listeners.

### Gesture Detection
- **Thresholds**: Configurable parameters for stroke length, angle, and squareness determine if a touch sequence counts as a gesture.
- **Listeners**:
  - `OnGestureListener`: Raw events (Start, Repeat, End, Cancel).
  - `OnGesturingListener`: State changes (Gesturing vs. Not Gesturing).
  - `OnGesturePerformedListener`: High-level callback when a complete gesture is finished.

### Rendering
- Uses a `Paint` object for stroking.
- Supports "uncertain" (while drawing) vs. "certain" (recognized) colors.
- Optimizes redraws using `mInvalidRect`.

## Java-to-C++ Translation Guide
- **UI Toolkit**: This is heavily tied to Android Views (`Canvas`, `MotionEvent`). Porting requires a target UI framework (e.g., Qt, custom Engine).
- **Logic Separation**: The core gesture capture logic (Points -> Path -> Gesture) can be separated from the View rendering logic.

## Source Reference
Defined in `GestureOverlayView.java`.
