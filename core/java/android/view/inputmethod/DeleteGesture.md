# DeleteGesture - Reverse Engineering Documentation

## Executive Summary
Handwriting gesture for deleting text within a specific area.

## Data Model
*   `mArea`: `RectF`.
*   `mGranularity`: Word or Character.
*   `mFallbackText`: String.

## Java-to-C++ Translation Guide
*   **Inheritance**: Inherits from `PreviewableHandwritingGesture` -> `HandwritingGesture`.
