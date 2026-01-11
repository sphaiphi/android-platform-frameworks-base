# CursorAnchorInfo - Reverse Engineering Documentation

## Executive Summary
Positional information about the text cursor and characters. Sent from the Editor to the IME to allow the IME to draw UI (like candidate windows) in the correct screen location.

## Data Model
*   **Selection**: `mSelectionStart`, `mSelectionEnd`.
*   **Composing**: `mComposingTextStart`, `mComposingText`.
*   **Insertion Marker**: Flags, horizontal/top/baseline/bottom positions (floats).
*   **Character Bounds**: `SparseRectFArray` mapping char index to bounds.
*   **Matrix**: `mMatrixValues` (3x3 matrix) for coordinate transformation.

## Java-to-C++ Translation Guide
*   **Matrix**: Uses 3x3 float array.
*   **RectF**: Floating point rectangles.
