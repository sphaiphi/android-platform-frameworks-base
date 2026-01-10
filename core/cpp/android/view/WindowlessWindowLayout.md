# WindowlessWindowLayout - Reverse Engineering Documentation

## Executive Summary
`WindowlessWindowLayout` is a specialized version of `WindowLayout` used for "Windowless" windows (e.g., content embedded via `SurfaceControlViewHost`). unlike regular windows, these are not affected by system-wide insets or cutouts; instead, they are strictly bound by the dimensions of their parent `SurfaceControl`.

## Architecture Overview
*   **Role**: Geometry calculator for embedded hierarchies.
*   **Inheritance**: `WindowLayout` -> `WindowlessWindowLayout`.

## Detailed Functionality
*   **`computeFrames()`**: Overrides the base logic to ignore display cutouts and system bars. It simply applies gravity within the parent's `attachedFrame`.

## Java-to-C++ Translation Guide
*   **Logic**: Simplifies the complex `computeFrames` into basic `Rect` arithmetic.

## Implementation Risks
*   **Mismatched Expectations**: If an app assumes it can query system bar insets from a windowless hierarchy, it will receive empty values.
