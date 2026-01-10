# ScaleGestureDetector - Reverse Engineering Documentation

## Executive Summary
`ScaleGestureDetector` detects "pinch-to-zoom" style gestures using multiple pointers. It calculates the distance between fingers over time and reports the scaling factor to the application via the `OnScaleGestureListener` callback. It also supports "Quick Scale" (double-tap and swipe) and "Stylus Scale" gestures.

## Architecture Overview
*   **Role**: Multi-touch scaling engine.
*   **Mechanism**: Tracks the "Span" (average distance between pointers) and "Focal Point" (center of all pointers).
*   **Gesture Types**:
    1.  **Pinch**: Standard two-finger zoom.
    2.  **Quick Scale**: Double-tap followed by a vertical swipe (one-handed zoom).
    3.  **Stylus Scale**: Pressing a stylus button followed by a swipe.

## Detailed Functionality

### 1. Span Calculation
*   **`mCurrSpan`** / **`mPrevSpan`**: The current and previous distance between pointers.
*   **`getScaleFactor()`**: Returns the ratio `mCurrSpan / mPrevSpan`.

### 2. Anchored Scaling
*   In "Quick Scale" or "Stylus Scale" modes, the focal point is fixed at the start of the gesture, and the scale factor is derived from the vertical distance moved by the finger/stylus.

### 3. Thresholds
*   **`mSpanSlop`**: Minimum distance change required to begin a scale gesture.
*   **`mMinSpan`**: Minimum distance fingers must be apart to be considered a scaling gesture.

## Java-to-C++ Translation Guide
*   **Math**: Uses `hypot()` for distance calculation.
*   **Event Analysis**: Iterates through all pointers in a `MotionEvent` to calculate the average focus and deviation.

## Implementation Risks
*   **Jitter**: Small finger movements can cause the scale factor to oscillate. The detector uses `mSpanSlop` to filter these out.
*   **Coordinate Drift**: If the focal point moves significantly during a pinch, the application must correctly handle the translation offset combined with the scale.
