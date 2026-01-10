# ChangeTransform - Reverse Engineering Documentation

## Executive Summary
`ChangeTransform` animates view transformations (scale, rotation, translation). It can also handle parenting changes by animating the view inside an overlay ("GhostView").

## Architecture
-   **Properties**: Matrix, Translation(X/Y/Z), Scale(X/Y), Rotation(X/Y/Z).
-   **Reparenting**: `mReparent` flag. If true, calculates transforms relative to the global window to handle views moving between different parents.

## Key Algorithms
-   **`captureValues`**: Captures raw transform properties and the composite Matrix. If reparenting, captures parent matrices.
-   **`createAnimator`**:
    -   If reparenting, sets up matrices to simulate the view's position in the new parent matching the old visual position.
    -   Uses `PathAnimatorMatrix` (inner class) to drive the view's matrix properties via `ObjectAnimator`.
    -   `GhostView`: If reparenting is involved, creates a ghost view in the scene root's overlay to render the view during transition, avoiding clipping issues in the new parent.

## Java-to-C++ Translation Guide
-   **Transforms**: standard 3D transforms.
-   **GhostView**: This is the hardest part. The C++ UI system needs a way to project a render node from a deep hierarchy into a root overlay layer while maintaining its visual state.
-   **Matrix Math**: Extensive use of `Matrix.postConcat`, `invert`, etc.
