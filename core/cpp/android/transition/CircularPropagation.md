# CircularPropagation - Reverse Engineering Documentation

## Executive Summary
`CircularPropagation` controls the start delay of animations so they appear to ripple out from an epicenter.

## Algorithm
-   **Epicenter**: Derived from `Transition.getEpicenter()` or the center of the ViewRoot.
-   **Distance**: Calculates Euclidean distance from epicenter to the center of the view.
-   **Delay**: `(distance / maxDistance) * duration`.
-   **Visibility**: If appearing (`MODE_IN`), farther views might delay longer. If disappearing (`MODE_OUT`), behavior may invert depending on implementation details in base class interactions.

## Java-to-C++ Translation Guide
-   **Math**: Simple geometry.
-   **Input**: Needs view coordinates relative to screen/root.
