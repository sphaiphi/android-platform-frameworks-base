# AccelerateDecelerateInterpolator - Reverse Engineering Documentation

## Executive Summary
An interpolator where the rate of change starts and ends slowly but accelerates through the middle.

## Key Algorithms
*   **`getInterpolation`**: Calculates `(cos((t + 1) * PI) / 2.0) + 0.5`. This creates a sinusoidal curve that eases in and eases out.

## Java-to-C++ Translation Guide
*   **Math**: Uses `java.lang.Math`. C++ equivalent is `std::cos` and `M_PI` (from `cmath`).
