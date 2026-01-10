# OvershootInterpolator - Reverse Engineering Documentation

## Executive Summary
An interpolator where the change flings forward and overshoots the last value then comes back.

## Key Algorithms
*   **`getInterpolation`**: `(t - 1)^2 * ((tension + 1) * (t - 1) + tension) + 1`. Default tension 2.0.

## Java-to-C++ Translation Guide
*   **Math**: Polynomial.
