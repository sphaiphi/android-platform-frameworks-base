# DecelerateInterpolator - Reverse Engineering Documentation

## Executive Summary
An interpolator where the rate of change starts out quickly and then decelerates.

## Key Algorithms
*   **`getInterpolation`**:
    *   If factor is 1.0: `1 - (1 - input)^2`.
    *   Otherwise: `1 - (1 - input)^(2 * factor)`.

## Java-to-C++ Translation Guide
*   **Math**: `std::pow`.
