# TransitionPropagation - Reverse Engineering Documentation

## Executive Summary
Abstract base class for customization of start delays in transitions (e.g. staggering animations).

## API Reference
-   **`getStartDelay`**: Returns the computed delay.
-   **`captureValues`**: Allows propagation to store view state (like position) needed for calculation.

## Java-to-C++ Translation Guide
-   **Strategy Pattern**: Algorithm injection.
