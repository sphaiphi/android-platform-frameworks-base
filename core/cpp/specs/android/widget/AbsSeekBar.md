# AbsSeekBar - Reverse Engineering Documentation

## Executive Summary
`AbsSeekBar` is an abstract base class extending `ProgressBar` that adds a draggable thumb. It provides the common logic for seekable progress bars like `SeekBar` and `RatingBar`, handling touch input to modify the progress level and drawing the thumb drawable.

## Architecture Overview
*   **Inheritance**: `View` -> `ProgressBar` -> `AbsSeekBar`.
*   **Role**: Base class for draggable progress widgets.
*   **Key Components**:
    *   `mThumb`: The drawable representing the draggable handle.
    *   `mTickMark`: Optional drawable drawn at intervals along the track.
    *   `onTouchEvent`: Handles user interaction (drag, tap) to update progress.

## Detailed Functionality

### 1. Thumb Management
*   **Drawing**: The thumb is drawn on top of the track. Its position is calculated based on the current progress relative to the min/max range.
*   **Offset**: `mThumbOffset` allows the thumb to extend beyond the bounds of the track (e.g., to center it on the end of the bar).
*   **Split Track**: `mSplitTrack` (boolean) determines if the track drawable should be masked out where the thumb is drawn (useful for transparent thumbs).

### 2. Touch Interaction
*   **Hit Detection**: Determines if a touch event starts a drag.
*   **Tracking**: Updates the progress value as the user moves their finger. It computes the scale (0.0 to 1.0) based on the x-coordinate relative to the view's width and padding.
*   **Key Input**: Supports incrementing/decrementing via D-pad or +/- keys (`mKeyProgressIncrement`).

### 3. Tick Marks
*   Supports drawing tick marks at equal intervals along the track, corresponding to the possible progress integer values.

## Java-to-C++ Translation Guide
*   **Input Handling**: Replicate `onTouchEvent` logic. The math for converting screen coordinates to progress is `scale = (x - paddingLeft) / availableWidth`.
*   **Drawing**: In `onDraw`, draw the track (via super), then draw tick marks (if any), then draw the thumb translated to the correct position.
*   **State**: Needs to track `mIsDragging` state to manage visual feedback (pressed state) and prevent parent views from intercepting touch events (`requestDisallowInterceptTouchEvent`).

## Implementation Risks
*   **Touch Slop**: Ensure proper touch slop handling to distinguish between scrolls and clicks/drags.
*   **RTL Support**: The calculation for thumb position needs to be inverted if the layout direction is Right-To-Left (`isLayoutRtl()`).
