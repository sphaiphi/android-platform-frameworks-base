# TextBoundsInfo - Reverse Engineering Documentation

## Executive Summary
Detailed layout information for a slice of text (character bounds, line/word/grapheme segments, BiDi levels). Used for handwriting gestures.

## Data Model
*   `mCharacterBounds`: Packed float array.
*   `mInternalCharacterFlags`: Packed int array (flags + bidi level).
*   `mLineSegmentFinder`, `mWordSegmentFinder`, `mGraphemeSegmentFinder`.

## Key Algorithms
*   **`getOffsetForPosition`**: Finds the character index closest to an (x, y) coordinate.
*   **`getRangeForRect`**: Finds text range inside a rectangle.

## Java-to-C++ Translation Guide
*   **Geometry**: Heavy geometric logic.
*   **Packed Arrays**: Memory optimization.
