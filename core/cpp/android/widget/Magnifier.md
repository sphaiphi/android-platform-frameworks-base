# Magnifier - Reverse Engineering Documentation

## Executive Summary
`Magnifier` is a utility class that displays a magnified copy of a `View`'s content in a floating window. It is used primarily by `Editor` for text selection handles. It supports a "fish-eye" distortion effect in newer versions.

## Architecture Overview
*   **Role**: Visual helper tool.
*   **Components**:
    *   `InternalPopupWindow`: A surface-backed window to draw the content.
    *   `PixelCopy`: Mechanism to capture the source view's pixels.
    *   `BLASTBufferQueue`: (Newer) Low-level surface compositing.

## Detailed Functionality
*   **`show(x, y)`**: Captures pixels from the source view around (x, y) and displays them zoomed in the popup window.
*   **Pixel Copy**: Uses `PixelCopy.request` to asynchronously fetch the rendered pixels from the Surface.
*   **Distortion**: Implements a mesh-based bitmap draw to create the fish-eye effect.

## Java-to-C++ Translation Guide
*   **Rendering**: Requires low-level access to the rendered frame buffer (texture copy) to be efficient. `PixelCopy` is an Android API; C++ engine needs an equivalent "ReadPixels" or "TextureToTexture" capability.
*   **Windowing**: Needs a separate overlay window.

## Implementation Risks
*   **Performance**: Reading back pixels from GPU to CPU (or even GPU to GPU) can be a bottleneck.
*   **Synchronization**: The magnifier content trails behind the actual view content by at least one frame.
