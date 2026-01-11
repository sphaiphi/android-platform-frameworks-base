# KeyButtonDrawable - Reverse Engineering Documentation

## Executive Summary
`KeyButtonDrawable` is a specialized Drawable for navigation buttons. It supports:
*   Tinting based on "dark intensity" (adapting to light/dark nav bar).
*   Shadows.
*   Rotation (e.g., for back button rotation).
*   Wrapping `AnimatedVectorDrawable`.

## Detailed Functionality
*   **Shadows**: Draws a blurred bitmap shadow behind the content.
*   **Rotation**: Can rotate the canvas.
*   **Hardware Acceleration**: Caches bitmaps (`mLastDrawnIcon`) to avoid re-rendering vector drawables excessively.

## Java-to-C++ Translation Guide
*   **Graphics**: Skia / Canvas operations. Shadow generation (Blur).
