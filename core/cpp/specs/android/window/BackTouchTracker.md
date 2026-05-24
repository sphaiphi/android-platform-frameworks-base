# BackTouchTracker - Reverse Engineering Documentation

## Executive Summary
`BackTouchTracker` processes raw `MotionEvent` coordinates during a back gesture to calculate a linear or non-linear progress value (0.0 to 1.0). It handles touch thresholds, restart logic (if a user reverses direction), and tracks the start location of the gesture.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` (Not Parcelable)
*   **Role**: Helper for state management and math utility.

## Detailed Functionality

### Progress Calculation (`getProgress(float touchX)`)
**Algorithm**:
1.  Determine `startX`. Usually `mInitTouchX`, but updates if gesture direction reverses (`mStartThresholdX`).
2.  Calculate `distance = abs(touchX - startX)`.
3.  **Linear Phase**: If `distance <= mLinearDistance`, `progress = distance / initialTarget`.
4.  **Non-Linear Phase**: If `distance > mLinearDistance`, linearly interpolates the remaining distance to `mMaxDistance`.
5.  Result is clamped [0, 1].

### State Management
*   **Initial**: Waiting for start.
*   **Active**: Gesture in progress.
*   **Finished**: Gesture complete.

### Touch Updates
*   Updates `mLatestTouchX`, `mLatestTouchY`.
*   Detects if the user moved back past the start threshold (cancellation intent) and updates `mStartThresholdX` to allow restarting the progress calculation from the new point.

## Data Model
*   `mLinearDistance`: Configurable threshold for linear mapping.
*   `mMaxDistance`: Max screen distance considered 100% progress.
*   `mNonLinearFactor`: Factor for the non-linear interpolation phase.

## Java-to-C++ Translation Guide

### Math
*   Uses `MathUtils.lerp`, `MathUtils.constrain`, `Math.max`. These have standard C++ `std::` equivalents or simple helper implementations.

### Logic
The logic is purely mathematical and state-based. Direct translation of the fields and the `getProgress` function is recommended.

## Implementation Risks
*   **System Properties**: `LINEAR_DISTANCE` is read from `persist.wm.debug.predictive_back_linear_distance`. C++ needs access to Android system properties (`__system_property_get`).
