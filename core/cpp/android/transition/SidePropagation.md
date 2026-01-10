# SidePropagation - Reverse Engineering Documentation

## Executive Summary
`SidePropagation` calculates start delays based on the view's distance to a specific screen edge (Left, Top, Right, Bottom). Used by `Slide`.

## Logic
-   **Distance**: Calculates Euclidean or linear distance from the view center to the configured side.
-   **Speed**: Adjusted by propagation speed factor.

## Java-to-C++ Translation Guide
-   **Geometry**: Boundary checks and distance math.
