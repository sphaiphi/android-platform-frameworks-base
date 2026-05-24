# ViewOutlineProvider - Reverse Engineering Documentation

## Executive Summary
`ViewOutlineProvider` defines how a `View` builds its physical `Outline`. The outline is used by the rendering system for two critical tasks: casting shadows (elevation) and clipping content (if `setClipToOutline` is enabled).

## Architecture Overview
*   **Role**: Boundary and shadow geometry provider.
*   **Default Providers**:
    *   `BACKGROUND`: Uses the `Outline` provided by the view's background drawable.
    *   `BOUNDS`: Uses a rectangular outline matching the view's dimensions.
    *   `PADDED_BOUNDS`: Matches the view's inner area after padding.

## Detailed Functionality
*   **`getOutline(View, Outline)`**: The primary callback. Subclasses implement this to define custom shapes (e.g., rounded rectangles, circles).

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Maps to `android::uirenderer::Outline`.
*   **Geometry**: Directly uses `android::graphics::Outline`.

## Implementation Risks
*   **Complex Shapes**: Non-rectangular outlines (like arbitrary paths) may not support shadow casting on all hardware platforms.
*   **Performance**: Outlines are re-queried whenever the view's size changes; complex path generation in `getOutline` should be avoided.
