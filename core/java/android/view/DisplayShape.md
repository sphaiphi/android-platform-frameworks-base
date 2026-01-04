# DisplayShape - Reverse Engineering Documentation

## Executive Summary
`DisplayShape` represents the physical boundary of a display. Unlike `DisplayCutout`, which focuses on "safe areas," `DisplayShape` provides a precise `Path` describing the entire physical shape of the display, including rounded corners and complex notch geometries.

## Architecture Overview
*   **Role**: Precise geometric boundary provider.
*   **Geometry**: Represented as an SVG-like specification string (`mDisplayShapeSpec`) parsed into a `graphics.Path`.
*   **Immutability**: The object is immutable; transformations return new instances.

## Detailed Functionality

### 1. Path Retrieval
*   **`getPath()`**: Returns the `Path` representing the display's shape in the current coordinate space (accounting for rotation and scaling).

### 2. Factory Methods
*   **`fromResources()`**: Loads the device-specific shape from system configuration strings.
*   **`createDefaultDisplayShape()`**: Generates a standard rectangle or circle if no specific hardware data is available.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Wrap a native `Path` implementation (e.g., Skia's `SkPath`).
*   **Parsing**: Use a C++ SVG path parser to interpret the specification string.

## Implementation Risks
*   **Rounding Accuracy**: Precise alignment between the `DisplayShape` and the actual rendered pixels is critical for features like "Edge Lighting" or custom rounded corner rendering.
*   **Performance**: The path should be cached after parsing, as regenerating a complex display shape from a string on every frame is expensive.
