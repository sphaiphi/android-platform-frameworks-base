# ChangeBounds - Reverse Engineering Documentation

## Executive Summary
`ChangeBounds` captures layout bounds (left, top, right, bottom) and clip bounds of target views before and after a scene change. It creates animators (`ObjectAnimator`) to morph the view from the starting state to the ending state.

## Architecture
-   **Inheritance**: Extends `Transition`.
-   **Properties Tracked**:
    -   `android:changeBounds:bounds` (Rect)
    -   `android:changeBounds:clip` (Rect)
    -   `android:changeBounds:parent` (View)
    -   `android:changeBounds:windowX/Y` (int)

## Data Model
-   **`mResizeClip`**: If true, resizes via `clipBounds` instead of view layout dimensions (used when view layout dimensions shouldn't change or complex clipping is needed).
-   **`mReparent`**: (Deprecated) Tracks parent changes to handle movement between containers.

## Key Algorithms
-   **`captureValues`**: Stores View's L/T/R/B and ClipBounds. Uses `getLocationInWindow` if reparenting.
-   **`createAnimator`**:
    -   Compares start and end values.
    -   If `mResizeClip` is false:
        -   Updates view layout using `setLeftTopRightBottom`.
        -   If both width and height change, animates `topLeft` and `bottomRight` simultaneously using `PropertyValuesHolder` and a `ViewBounds` utility class to prevent layout artifacts during animation.
    -   If `mResizeClip` is true:
        -   Sets the view to the larger of start/end dimensions.
        -   Animates `clipBounds` (`Rect`) to reveal/hide content.
        -   Animates translation/position.
    -   If parent changes (and `mReparent` is true): Creates a `BitmapDrawable` copy of the view, adds it to the overlay, and animates it to the new position.

## Inner Classes
-   **`ViewBounds`**: Helper to set left/top and right/bottom separately but commit them to the View only when both have been updated for a frame (prevents intermediate invalid layout states).

## Java-to-C++ Translation Guide
-   **View System**: Heavily coupled with Android View system (`setLeftTopRightBottom`, `setClipBounds`). C++ equivalents need access to the layout engine nodes.
-   **Animation**: Uses `ObjectAnimator` and `Property`. C++ needs an animation framework (e.g., interpolated values driving render properties).
-   **Drawable/Bitmap**: The reparenting logic involves snapshotting a View to a Bitmap.
