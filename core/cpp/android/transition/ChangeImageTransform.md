# ChangeImageTransform - Reverse Engineering Documentation

## Executive Summary
`ChangeImageTransform` animates an `ImageView`'s matrix. This is used to smooth transitions where an image changes scale type (e.g., CenterCrop to FitCenter) or the matrix itself changes.

## Architecture
-   **Target**: Specifically `ImageView`.
-   **Logic**: Captures the visual matrix of the image and animates it.

## Key Algorithms
-   **`captureValues`**:
    -   Extracts `Drawable` bounds and `ImageView` scale type.
    -   Calculates a `Matrix` representing the image transform.
    -   Handles `FIT_XY` specifically by calculating scaling factors based on view bounds vs drawable dimensions.
-   **`createAnimator`**:
    -   Compares start/end Matrices.
    -   If they differ, creates an `ObjectAnimator` on a custom `ANIMATED_TRANSFORM_PROPERTY` of the ImageView.
    -   Uses `TransitionUtils.MatrixEvaluator` to interpolate matrices.

## Java-to-C++ Translation Guide
-   **Specifics**: This is tightly bound to `ImageView`. If the C++ UI framework has a generic "Image" element with transform matrices, logic applies.
-   **Matrix Interpolation**: Requires decomposing matrices or simple element-wise interpolation (as done in `MatrixEvaluator`).
