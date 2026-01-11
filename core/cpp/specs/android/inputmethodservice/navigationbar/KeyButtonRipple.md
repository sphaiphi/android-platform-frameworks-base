# KeyButtonRipple - Reverse Engineering Documentation

## Executive Summary
`KeyButtonRipple` renders the ripple effect for navigation buttons. It supports hardware-accelerated rendering (RenderNodeAnimator) for high performance.

## Detailed Functionality
*   **Hardware vs Software**: Checks `canvas.isHardwareAccelerated()`. Uses `RenderNodeAnimator` for HW, standard `Canvas` draw calls for SW.
*   **Animations**: Scale and Alpha animations on press/release.
*   **Shapes**: Supports Oval and Rounded Rect.

## Java-to-C++ Translation Guide
*   **RenderNode**: This is specific to Android's HWUI pipeline. C++ implementation would need to interface with the rendering pipeline (e.g., Skia RenderNode).
