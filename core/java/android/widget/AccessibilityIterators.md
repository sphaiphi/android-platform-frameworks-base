# AccessibilityIterators - Reverse Engineering Documentation

## Executive Summary
`AccessibilityIterators` is a package-private utility class containing implementations of `TextSegmentIterator`. These iterators are used by accessibility services (TalkBack, etc.) to traverse text content at different granularities (specifically lines and pages) that aren't natively supported by `ICU` or standard Java text iterators.

## Architecture Overview
*   **Role**: Text traversal helper for Accessibility.
*   **Key Classes**:
    *   `LineTextSegmentIterator`: Iterates text line-by-line using `android.text.Layout`.
    *   `PageTextSegmentIterator`: Iterates text page-by-page (visible screen area) using `TextView` geometry.

## Detailed Functionality

### 1. LineTextSegmentIterator
*   **Dependency**: Requires a `Spannable` text and a `Layout` object.
*   **Logic**: Uses `Layout.getLineForOffset()` to determine line boundaries.
*   **Direction**: Handles traversal start (`-1`) and end (`1`).

### 2. PageTextSegmentIterator
*   **Dependency**: Extends `LineTextSegmentIterator` but needs a `TextView`.
*   **Logic**:
    *   Uses `mView.getGlobalVisibleRect()` to find the view's height on screen.
    *   Calculates how many lines fit in that height.
    *   Jumps offset by that vertical distance to find the next "page" boundary.

## Java-to-C++ Translation Guide
*   **Text Layout**: Heavily relies on the specific text layout engine (`android.text.Layout`). C++ implementation requires access to the equivalent text shaping/layout engine (e.g., Minikin/Skia) to determine line breaks.
*   **Geometry**: Needs access to the view's clipped bounds to calculate page size.

## Implementation Risks
*   **Text Layout Consistency**: If the C++ text layout engine differs from the Java one, line breaks might not match, causing accessibility navigation issues.
