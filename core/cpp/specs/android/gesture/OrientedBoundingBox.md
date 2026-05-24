# OrientedBoundingBox - Reverse Engineering Documentation

## Executive Summary
`OrientedBoundingBox` represents a rectangular bounding box that can be rotated. It differs from standard `RectF` which is axis-aligned.

## Data Model
- `orientation`: Angle of rotation.
- `width`, `height`, `centerX`, `centerY`.
- `squareness`: Ratio of width/height (normalized to be <= 1).

## Detailed Functionality
- **`toPath()`**: Generates a `Path` representation of the rotated box (useful for debug drawing).

## Java-to-C++ Translation Guide
- **Geometry**: Basic geometric struct.

## Source Reference
Defined in `OrientedBoundingBox.java`.
