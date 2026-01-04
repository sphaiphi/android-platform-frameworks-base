# AnticipateOvershootInterpolator - Reverse Engineering Documentation

## Executive Summary
An interpolator where the change starts backward, flings forward, overshoots, and settles. Combines Anticipate and Overshoot logic.

## Key Algorithms
*   **`getInterpolation`**:
    *   If `t < 0.5`: scaled Anticipate logic.
    *   If `t >= 0.5`: scaled Overshoot logic.
    *   Tension is typically multiplied by 1.5 to accentuate the effect given the split timeframe.

## Java-to-C++ Translation Guide
*   **Math**: Piecewise function.
