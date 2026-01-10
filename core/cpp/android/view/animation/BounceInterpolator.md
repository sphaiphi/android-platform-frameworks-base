# BounceInterpolator - Reverse Engineering Documentation

## Executive Summary
An interpolator where the change bounces at the end. Simulates a ball dropping and bouncing.

## Key Algorithms
*   **`getInterpolation`**: Piecewise function simulating physics of bouncing (parabolic sections).
    *   `t < 0.3535`: `t^2 * 8`.
    *   Other segments use offsets and scaling to create smaller bounces.

## Java-to-C++ Translation Guide
*   **Math**: Piecewise quadratic functions.
