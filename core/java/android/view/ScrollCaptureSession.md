# ScrollCaptureSession - Reverse Engineering Documentation

## Executive Summary
`ScrollCaptureSession` represents the active scope of a scroll capture operation. It provides the `Surface` used to transfer image buffers between the application and the screenshot tool and contains metadata about the coordinate system for the session.

## Data Model
*   **`mSurface`**: `Surface` - The buffer queue where the app renders its content.
*   **`mScrollBounds`**: `Rect` - The total area identified as scrollable content.
*   **`mPositionInWindow`**: `Point` - The offset of the scroll bounds relative to the window origin.

## Detailed Functionality
*   **Buffer Transfer**: The `Surface` is the primary pipe for the pixel data.
*   **Coordinate Context**: The `mPositionInWindow` is essential for the remote tool to stitch multiple captured images into a single long screenshot correctly.

## Java-to-C++ Translation Guide
*   **Structure**: In C++, this can be a simple `class` or `struct` wrapping an `sp<Surface>`.

## Implementation Risks
*   **Surface Validity**: The application must not close or release the `Surface` until the session has officially ended.
