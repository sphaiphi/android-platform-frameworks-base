# MagnificationSpec - Reverse Engineering Documentation

## Executive Summary
`MagnificationSpec` defines the parameters for screen magnification (zoom). It encapsulates a scaling factor and the X/Y offsets required to center the zoomed content on a specific focal point.

## Data Model
*   **`scale`**: `float` - The multiplier for the zoom level (must be >= 1.0).
*   **`offsetX` / `offsetY`**: `float` - The translation applied after scaling, in screen-relative pixels.

## Detailed Functionality
*   **`isNop()`**: Checks if the spec represents a "No-Operation" (scale = 1.0, no offsets).
*   **Parcelable**: Used extensively in IPC between `AccessibilityManagerService` and the `WindowManager` to synchronize magnification states.

## Java-to-C++ Translation Guide
*   **Mapping**: Map to `android::view::MagnificationSpec`.
*   **Parceling**: Serialization must match the native implementation in `frameworks/native/libs/gui/`.

## Implementation Risks
*   **Invalid Scales**: A scale less than 1.0 is logically invalid for magnification and should be guarded against.
*   **Coordinate Overflow**: Large offsets can cause content to be shifted completely off-screen.
