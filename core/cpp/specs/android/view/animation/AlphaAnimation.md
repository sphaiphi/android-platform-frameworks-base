# AlphaAnimation - Reverse Engineering Documentation

## Executive Summary
An animation that controls the alpha level of an object. Useful for fading things in and out.

## Data Model
*   `mFromAlpha`: Starting alpha value.
*   `mToAlpha`: Ending alpha value.

## Key Algorithms
*   **`applyTransformation`**: Calculates `alpha = mFromAlpha + ((mToAlpha - mFromAlpha) * interpolatedTime)` and sets it on the `Transformation` object.

## Java-to-C++ Translation Guide
*   **Linear Interpolation**: Standard linear interpolation logic.
