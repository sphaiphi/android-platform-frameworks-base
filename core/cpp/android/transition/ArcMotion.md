# ArcMotion - Reverse Engineering Documentation

## Executive Summary
`ArcMotion` is a subclass of `PathMotion` used to generate a curved path (using a cubic Bezier) between two points on an imaginary circle. It is typically used in transitions (like `ChangeBounds`) to move views along a curve rather than a straight line.

## Architecture
- **Inheritance**: Extends `PathMotion`.
- **Role**: Provides a concrete algorithm for `getPath(startX, startY, endX, endY)`.

## Data Model
- **Configuration Attributes**:
    - `mMinimumHorizontalAngle` (float): Minimum arc angle when points are horizontally aligned.
    - `mMinimumVerticalAngle` (float): Minimum arc angle when points are vertically aligned.
    - `mMaximumAngle` (float): Maximum arc angle (default 70 degrees).
- **Derived Values**:
    - Tangents (tan(angle/2)) are pre-calculated for performance.

## Algorithm: `getPath`
1.  **Inputs**: Start (x,y) and End (x,y).
2.  **Logic**:
    *   Calculates the midpoint and the vector between start and end.
    *   Determines if the motion is primarily horizontal or vertical based on `deltaX` vs `deltaY`.
    *   If primarily horizontal, the "center" of the circle is aligned vertically with the end point.
    *   If primarily vertical, the "center" is aligned horizontally with the end point.
    *   Uses the configured minimum/maximum angles to adjust the "bulge" (distance of control points).
    *   Calculates a cubic Bezier curve (`cubicTo`) where control points are derived to approximate the circular arc.
3.  **Output**: A `Path` object starting at (startX, startY) and ending at (endX, endY).

## API Reference
-   `set/getMinimumHorizontalAngle(float)`: Control curvature for horizontal motion.
-   `set/getMinimumVerticalAngle(float)`: Control curvature for vertical motion.
-   `set/getMaximumAngle(float)`: Limits the curvature.
-   `getPath(...)`: The core generation method.

## Java-to-C++ Translation Guide
-   **Math**: Relies on `Math.tan`, `Math.toDegrees`, `Math.hypot`, `Math.sqrt`. C++ `<cmath>` equivalents are standard.
-   **Graphics**: Returns `android.graphics.Path`. In C++, this would likely map to `SkPath` (Skia) or a generic path structure supporting `moveTo` and `cubicTo`.
-   **XML Inflation**: Reads attributes from `R.styleable.ArcMotion`. C++ implementation would need a mechanism to parse these from resources or a property map.
