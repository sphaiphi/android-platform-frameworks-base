# ClipRectAnimation - Reverse Engineering Documentation

## Executive Summary
An animation that animates the clip bounds (`setClipRect`) of a Transformation.

## Data Model
*   `mFromRect`, `mToRect`: Start and end clip rectangles.
*   Resolves values (absolute, relative to self, relative to parent) similar to TranslateAnimation.

## Key Algorithms
*   **`applyTransformation`**: Linearly interpolates left, top, right, bottom between start and end rects and calls `tr.setClipRect`.

## Java-to-C++ Translation Guide
*   **Rect**: Uses `android.graphics.Rect`. C++ equivalent `SkRect` or similar struct.
