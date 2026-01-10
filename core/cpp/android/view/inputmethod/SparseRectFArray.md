# SparseRectFArray - Reverse Engineering Documentation

## Executive Summary
Optimized SparseArray for `RectF` objects, used in `CursorAnchorInfo` to send character bounds efficiently.

## Data Model
*   `mKeys`: int array.
*   `mCoordinates`: float array (packed x, y, w, h).
*   `mFlagsArray`: int array.

## Java-to-C++ Translation Guide
*   **Data Structure**: Efficient packed array.
