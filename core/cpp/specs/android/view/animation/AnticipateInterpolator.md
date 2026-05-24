# AnticipateInterpolator - Reverse Engineering Documentation

## Executive Summary
An interpolator where the change starts backward then flings forward.

## Key Algorithms
*   **`getInterpolation`**: `t * t * ((tension + 1) * t - tension)`. Default tension is 2.0.

## Java-to-C++ Translation Guide
*   **Math**: Simple polynomial.
