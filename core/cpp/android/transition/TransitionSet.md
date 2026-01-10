# TransitionSet - Reverse Engineering Documentation

## Executive Summary
A `Transition` that holds a collection of child transitions.

## Data Model
-   **`mTransitions`**: List of children.
-   **`mPlayTogether`**: Boolean (Sequential vs Together).

## Key Algorithms
-   **`createAnimators`**: Iterates children. If sequential, calculates start delays cumulatively.
-   **`runAnimators`**: Sets up listeners. If sequential, the end of one triggers the start of the next.

## Java-to-C++ Translation Guide
-   **Composite**: Standard composite pattern. Recursion used for capture/create calls.
