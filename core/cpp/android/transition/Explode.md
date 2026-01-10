# Explode - Reverse Engineering Documentation

## Executive Summary
`Explode` is a `Visibility` transition where views translate out of (or into) the scene from the edges, appearing to explode from a central point.

## Logic
-   **Propagation**: Defaults to `CircularPropagation`.
-   **`calculateOut`**: Determines the translation vector.
    -   Vector = Center of View - Epicenter.
    -   Normalizes vector and scales it to push the view off-screen.
-   **Animator**: Uses `TranslationAnimationCreator` to animate `translationX` and `translationY`.

## Java-to-C++ Translation Guide
-   **Geometry**: Calculation of intersection with screen bounds to ensure the view travels far enough to leave the screen.
