# Scroller - Reverse Engineering Documentation

## Executive Summary
`Scroller` is a legacy physics helper class used to calculate scrolling positions over time. It supports simple "scroll to" animations and momentum-based "flings". It is generally superseded by `OverScroller` but remains for backward compatibility.

## Architecture Overview
*   **Role**: Math / Physics Engine.
*   **Dependencies**: `Interpolator`, `Context` (for density).

## Detailed Functionality

### 1. Physics Models
*   **Scroll Mode (`SCROLL_MODE`)**: Simple interpolation from start to end over a fixed duration using the provided `Interpolator` (default is `ViscousFluidInterpolator`).
*   **Fling Mode (`FLING_MODE`)**: Simulates physical deceleration due to friction.
    *   Uses a spline curve (`SPLINE_POSITION`, `SPLINE_TIME`) to map time to distance.
    *   **Friction**: Calculated based on device PPI (`mPpi`) and a friction coefficient (`mFlingFriction`).
    *   **Flywheel**: If a new fling starts while the previous one is active, their velocities are accumulated (if in the same direction).

### 2. Math Constants
*   `DECELERATION_RATE`: Logarithmic decay rate.
*   `INFLEXION`: Tension point for the spline.
*   Spline tables are pre-calculated static arrays.

### 3. The `computeScrollOffset` Loop
*   Called by the view during drawing.
*   Calculates `timePassed`.
*   If in fling mode: `mCurrVelocity = velocityCoef * mDistance / mDuration * 1000.0f`.
*   Updates `mCurrX` and `mCurrY`.

## Java-to-C++ Translation Guide
*   **Spline**: The static spline generation code in the `static {}` block must be ported precisely to match Android's scroll feel.
*   **ViscousFluidInterpolator**: A custom interpolator often used by standard lists. Port the `viscousFluid` function.

## Implementation Risks
*   **Floating Point**: Precision differences could lead to minor visual discrepancies, but usually negligible.
*   **Density**: Correctly accessing screen DPI (`mPpi`) is crucial for the physics to feel right on different screens.
