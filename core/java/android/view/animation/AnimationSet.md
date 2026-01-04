# AnimationSet - Reverse Engineering Documentation

## Executive Summary
A container for playing multiple `Animation` objects together. It aggregates transformations from its children into a single `Transformation`.

## Architecture
*   **Aggregation**: Holds an `ArrayList<Animation>`.
*   **Property Inheritance**: Properties like `duration`, `fillBefore`, `fillAfter` set on the set are pushed down to children during initialization.

## Key Algorithms
*   **`getTransformation`**:
    1.  Iterates through all child animations.
    2.  Calls `child.getTransformation` into a temp transformation.
    3.  Composes the temp transformation into the result transformation.
    4.  Manages the lifecycle (start/end) based on children's state.
*   **`initialize`**: Pushes configuration (duration, interpolator) down to children.

## Java-to-C++ Translation Guide
*   **Composite Pattern**: Standard composite pattern implementation.
