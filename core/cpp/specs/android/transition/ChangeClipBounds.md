# ChangeClipBounds - Reverse Engineering Documentation

## Executive Summary
`ChangeClipBounds` is a specific transition that animates changes to the `clipBounds` property of a View. It is useful when only the clipping region changes, not the view's layout dimensions.

## Data Model
-   **Properties**:
    -   `android:clipBounds:clip` (Rect)
    -   `android:clipBounds:bounds` (Rect - fallback if clip is null)

## Key Algorithms
-   **`captureValues`**: Stores `view.getClipBounds()`.
-   **`createAnimator`**:
    -   If start/end clips match, returns null.
    -   Uses `ObjectAnimator.ofObject` with `RectEvaluator` to animate the `clipBounds` property.
    -   Handles `null` clip bounds by substituting the view's layout bounds.

## Java-to-C++ Translation Guide
-   **Clip Rects**: Maps directly to animation of a clipping rectangle on a RenderNode or UI element.
-   **Evaluator**: `RectEvaluator` logic (linear interpolation of L, T, R, B) is standard.
