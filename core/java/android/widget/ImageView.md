# ImageView - Reverse Engineering Documentation

## Executive Summary
`ImageView` is a specialized `View` for displaying images (`Bitmap`, `Drawable`, or `Icon`). It provides built-in support for scaling, tinting, and aspect ratio management.

## Architecture Overview
*   **Inheritance**: `View` -> `ImageView`.
*   **Core State**:
    *   `mDrawable`: The actual content being rendered.
    *   `mScaleType`: The strategy for fitting the drawable into the view bounds.
    *   `mDrawMatrix`: The transformation matrix applied during drawing.

## Detailed Functionality

### 1. Scaling (`ScaleType`)
*   **`CENTER_CROP`**: Scales the image uniformly to fill the view, clipping the excess.
*   **`FIT_CENTER`**: Scales uniformly so the image fits entirely within the view.
*   **`MATRIX`**: Uses a custom `Matrix` supplied via `setImageMatrix()`.

### 2. Rendering (`onDraw`)
*   If `mDrawable` is null, it does nothing.
*   Otherwise, it applies the `mDrawMatrix` to the `Canvas` and calls `mDrawable.draw(canvas)`.
*   Supports alpha blending and color filtering (`tint`).

### 3. Aspect Ratio Management
*   **`adjustViewBounds`**: If true, the `ImageView` will resize its own width or height to maintain the drawable's aspect ratio during the measure pass.

## Java-to-C++ Translation Guide
*   **Drawable Mapping**: In C++, `Drawable` can be mapped to a polymorphic `Renderable` class or a simple texture reference.
*   **Matrix Math**: Use `android::Matrix` (or a similar GLM-style library) for the `mDrawMatrix` calculations.
*   **Resource Loading**: C++ should handle asynchronous image decoding (e.g., using `libpng` or `libjpeg-turbo`) to avoid blocking the main loop.

## Implementation Risks
*   **Bitmap Memory**: `ImageView` often holds large `BitmapDrawable` objects. In C++, ensure that texture memory is freed when the view is detached.
*   **Scale Precision**: Improper floating-point math in the matrix calculations can lead to blurry images (sub-pixel misalignment).
