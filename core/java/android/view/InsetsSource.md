# InsetsSource - Reverse Engineering Documentation

## Executive Summary
`InsetsSource` represents a single entity (like a Status Bar, Navigation Bar, or IME) that provides insets to other windows. It contains the geometry (frame), visibility status, and various behavioral flags for that specific inset.

## Data Model

### Core Fields
*   **`mId`**: `int` - A unique identifier for the source.
*   **`mType`**: `int` - The bitmask representing the public `InsetsType`.
*   **`mFrame`**: `Rect` - The physical bounds of the source in screen coordinates.
*   **`mVisible`**: `boolean` - Whether the source is currently active.

### Geometry Hints
*   **`mSideHint`**: Indicates which side of the screen the source is docked to (Left, Top, Right, Bottom).
*   **`mBoundingRects`**: Detailed sub-rectangles for complex shapes (e.g., custom window headers).

## Detailed Functionality
*   **`calculateInsets()`**: The core logic for determining the `Insets` (L, T, R, B) caused by this source relative to a window's frame.
*   **`createId()`**: Static utility to pack owner hash, index, and type into a single 32-bit ID.

## Java-to-C++ Translation Guide
*   **Primary Type**: Map to `android::InsetsSource`.
*   **ID Packing**: Top 16 bits = Owner, Middle 11 bits = Index, Bottom 5 bits = Type.

## Implementation Risks
*   **Intersection Logic**: `calculateInsets` must handle edge cases where the window doesn't fully overlap with the source or where the source is floating.
