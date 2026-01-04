# InsetsAnimationSpec - Reverse Engineering Documentation

## Executive Summary
`InsetsAnimationSpec` is an internal interface used to define the timing and curve parameters for a window insets animation. it allows the system to pick different durations and interpolators based on the type of inset being animated (e.g., a standard keyboard vs. a floating IME).

## Detailed Functionality
*   **`getDurationMs()`**: Returns the total length of the animation.
*   **`getInsetsInterpolator()`**: Returns the `Interpolator` used to map time to progress.

## Java-to-C++ Translation Guide
*   **Interface**: Map to a C++ virtual interface.
*   **Standard Specs**: Provide default implementations for "Move In", "Move Out", and "IME Sync".

## Implementation Risks
*   **Sync Disparity**: If the duration returned here doesn't match the actual RenderThread animation length, the visual transition will be jerky.
