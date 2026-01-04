# DeleteRangeGesture - Reverse Engineering Documentation

## Executive Summary
Handwriting gesture for deleting text in a range defined by a start area and an end area (e.g., across multiple lines).

## Data Model
*   `mStartArea`: `RectF`.
*   `mEndArea`: `RectF`.
*   `mGranularity`.

## Java-to-C++ Translation Guide
*   **Inheritance**: Inherits from `PreviewableHandwritingGesture`.
