# Rotate - Reverse Engineering Documentation

## Executive Summary
`Rotate` animates the `rotation` property of a View.

## Logic
-   **Capture**: `view.getRotation()`.
-   **Animation**: `ObjectAnimator.ofFloat`.

## Java-to-C++ Translation Guide
-   **Transforms**: Maps to rotation transform animation.
