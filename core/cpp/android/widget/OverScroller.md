# OverScroller - Reverse Engineering Documentation

## Executive Summary
`OverScroller` acts as a physics engine for scrolling animations. It supports "overshooting" (spring-back) boundaries. It replaces the older `Scroller`.

## Architecture Overview
*   **Components**: `SplineOverScroller` (two instances, X and Y).
*   **Role**: Physics calculation (does not modify views directly).

## Detailed Functionality
*   **Fling**: Calculates a trajectory based on initial velocity and friction (`SplineOverScroller`).
*   **Springback**: Calculates a parabolic path to return to valid bounds when overscrolled.
*   **Compute**: `computeScrollOffset()` updates the internal current position based on elapsed time.

## Java-to-C++ Translation Guide
*   **Math**: The spline interpolation logic (`SPLINE_POSITION`, `SPLINE_TIME`) is precise math that should be ported exactly to maintain the standard Android scroll "feel".
*   **Physics**: Gravity-based deceleration for springback.

## Implementation Risks
*   **Math**: Floating point precision issues.
*   **Feel**: Deviating from the spline constants makes scrolling feel "wrong" or "non-native".
