# RoundedCorner - Reverse Engineering Documentation

## Executive Summary
`RoundedCorner` represents a single rounded corner of a display. It encapsulates the geometry of the corner, providing the radius and the center point of the quarter-circle that approximates the physical display corner. It is used by applications to avoid placing interactive elements in non-square screen areas.

## Data Model
*   **`mPosition`**: `int` - One of `TOP_LEFT`, `TOP_RIGHT`, `BOTTOM_RIGHT`, `BOTTOM_LEFT`.
*   **`mRadius`**: `int` - The radius of the corner in pixels.
*   **`mCenter`**: `Point` - The coordinate of the center of the circle forming the corner.

## Detailed Functionality
*   **Immutability**: The object is immutable.
*   **Empty State**: `isEmpty()` returns true if the radius is 0 or if the corner is not relevant to the current window bounds.

## Java-to-C++ Translation Guide
*   **Structure**: Map to a C++ `class RoundedCorner`.
*   **Parcelling**: Marshalling order: Position, Radius, Center X, Center Y.

## Implementation Risks
*   **Approximation**: Physical corners may not be perfect quarter-circles. The system uses this model as a "safe" boundary.
*   **Scaling**: Radius and center points must be scaled correctly when the display density changes.
