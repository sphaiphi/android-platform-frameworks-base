# Animation - Reverse Engineering Documentation

## Executive Summary
The abstract base class for all tweened animations. It handles timing, repetition, listeners, interpolators, and the core animation lifecycle loop.

## Architecture
*   **State Machine**: Tracks `mStarted`, `mEnded`, `mInitialized`.
*   **Timing**: Uses `mStartTime`, `mDuration`, `mStartOffset`.
*   **Transformation**: The `getTransformation` method calculates the interpolated time and calls `applyTransformation` (implemented by subclasses) to modify a `Transformation` object.

## Key Algorithms
*   **`getTransformation(currentTime, outTransformation)`**:
    1.  Calculates normalized time based on `currentTime`, `mStartTime`, `mDuration`.
    2.  Handles `mFillBefore`, `mFillAfter`, `mRepeatCount`, `mRepeatMode`.
    3.  Calls `mInterpolator.getInterpolation` to get `interpolatedTime`.
    4.  Calls `applyTransformation(interpolatedTime, outTransformation)`.
*   **`resolveSize`**: Helper to convert relative dimensions (ABSOLUTE, RELATIVE_TO_SELF, RELATIVE_TO_PARENT) into pixels.

## Java-to-C++ Translation Guide
*   **Time**: Uses milliseconds (`long`). C++ typically uses `std::chrono` or raw `int64_t`.
*   **Cloneable**: Implements `Cloneable`. C++ copy constructors/assignment operators should be defined.
*   **Virtual Methods**: `applyTransformation` is the main extension point.
