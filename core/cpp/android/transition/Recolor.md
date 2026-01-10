# Recolor - Reverse Engineering Documentation

## Executive Summary
`Recolor` animates background color and/or text color.

## Logic
-   **Capture**: Gets `Background` (if `ColorDrawable`) and `TextColor`.
-   **Animation**: Uses `ObjectAnimator.ofArgb`.

## Java-to-C++ Translation Guide
-   **Interpolation**: Needs RGB/ARGB interpolation support.
