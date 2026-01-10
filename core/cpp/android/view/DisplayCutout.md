# DisplayCutout - Reverse Engineering Documentation

## Executive Summary
`DisplayCutout` represents the non-functional areas of a display (notches, punch-holes) and "waterfall" curved edges. It provides applications with "safe insets" to ensure that critical UI elements are not obscured by physical hardware features.

## Data Model

### 1. Insets
*   **Safe Insets**: `Rect` - The minimum amount a window must be inset from each edge to avoid the cutout.
*   **Waterfall Insets**: `Insets` - Describes the width/height of the curved edges on a waterfall display.

### 2. Geometry
*   **Bounding Rects**: A set of four rectangles (`left`, `top`, `right`, `bottom`) describing the exact pixel bounds of the cutouts.
*   **Cutout Path**: A `graphics.Path` object for precise rendering or hit-testing against the cutout shape.

## Detailed Functionality

### 1. Rotation Support
*   **`getRotated()`**: Calculates new insets and bounds when the display orientation changes (e.g., 0° to 90°).

### 2. Inset Logic
*   **`inset()`**: Adjusts the cutout information when the window itself is inset (e.g., in multi-window mode).

### 3. Resource Loading
*   **`fromResourcesRectApproximation()`**: Parses system configuration strings to initialize the cutout geometry for the specific device hardware.

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap `android::DisplayCutout`.
*   **Parceling**: Uses a `ParcelableWrapper` for binder communication. Serialization must be bit-compatible with `frameworks/native/libs/ui/DisplayCutout.cpp`.

## Implementation Risks
*   **Immutability**: `DisplayCutout` is designed to be immutable. Any modification should return a new instance to prevent side effects in the view hierarchy.
*   **Coordinate Space**: Bounding rects and paths must be carefully managed across screen-space, window-space, and view-local coordinates.
