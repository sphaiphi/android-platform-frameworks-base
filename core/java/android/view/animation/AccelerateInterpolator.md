# AccelerateInterpolator - Reverse Engineering Documentation

## Executive Summary
An interpolator where the rate of change starts out slowly and then accelerates.

## Data Model
*   `mFactor`: Degree to which the animation should be eased. Default is 1.0.
*   `mDoubleFactor`: 2 * `mFactor`.

## Key Algorithms
*   **`getInterpolation`**:
    *   If factor is 1.0: `input * input` (quadratic).
    *   Otherwise: `pow(input, 2 * factor)`.

## Java-to-C++ Translation Guide
*   **Math**: Uses `java.lang.Math.pow`. C++ equivalent is `std::pow`.
