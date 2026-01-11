# RoundScrollbarRenderer - Reverse Engineering Documentation

## Executive Summary
`RoundScrollbarRenderer` is a specialized drawing utility for circular Wear OS devices. It renders curved scrollbars that follow the physical edge of a round screen. It handles the mapping between linear scroll offsets and angular positions, ensuring that scrollbars remain visible and correctly positioned on circular displays.

## Architecture Overview
*   **Role**: Circular UI component renderer.
*   **Geometry**: Translates scroll ranges into angles (default range: 28.8°).
*   **Configuration**: Supports a "Refactored" mode for modern devices (controlled by `persist.cw_build.bluechip.enabled`).

## Detailed Functionality

### 1. Angle Calculation
*   **`computeSweepAngle()`**: Converts the "scroll extent" (visible portion) into an arc length.
*   **`computeStartAngle()`**: Maps the "scroll offset" to a position on the circular track.

### 2. Smooth Resizing
*   **`resizeGradually()`**: Implements a dampening effect (`RESIZING_RATE` = 0.8) so the scrollbar doesn't jump abruptly when the underlying content size changes.

### 3. Rendering
*   **`drawTrack()`** / **`drawArc()`**: Uses `Canvas.drawArc` to render the thumb and the background track.
*   **Insetting**: Automatically insets the scrollbar based on the `circular_display_mask_thickness` to prevent it from being clipped by the physical bezel.

## Java-to-C++ Translation Guide
*   **Math**: Relies heavily on trigonometry (`acos`, `sin`, `toDegrees`).
*   **Geometry**: Uses `android::RectF` for the bounding box of the circular arc.

## Implementation Risks
*   **Coordinate mapping**: The renderer must correctly handle `drawToLeft` for devices configured for left-handed use.
*   **Visual Continuity**: The angular mapping must ensure that the scrollbar reaches the top and bottom of its track exactly when the content does.
