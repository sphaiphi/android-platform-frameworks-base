# CycleInterpolator - Reverse Engineering Documentation

## Executive Summary
Repeats the animation for a specified number of cycles. The rate of change follows a sinusoidal pattern.

## Key Algorithms
*   **`getInterpolation`**: `sin(2 * cycles * PI * input)`.

## Java-to-C++ Translation Guide
*   **Math**: `std::sin`.
