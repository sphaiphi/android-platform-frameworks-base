# ScrollCaptureCallback - Reverse Engineering Documentation

## Executive Summary
`ScrollCaptureCallback` is the interface that an application (or a specific `View`) implements to support "Long Screenshots" (Scroll Capture). it defines the protocol for the system to search for scrollable content, prepare for a capture session, and request image buffers for specific regions of the scrollable area.

## Detailed Functionality

### 1. Discovery (`onScrollCaptureSearch`)
*   The view reports its "Scroll Bounds" (the area containing the scrollable content) to the system.

### 2. Session Lifecycle (`onScrollCaptureStart` / `onScrollCaptureEnd`)
*   **Start**: The view prepares for capture (e.g., pausing animations, allocating buffers).
*   **End**: The view cleans up and returns to its normal interactive state.

### 3. Image Acquisition (`onScrollCaptureImageRequest`)
*   The system requests a specific `Rect` within the scroll bounds. The view must render that area into the provided `Surface`.

## Java-to-C++ Translation Guide
*   **Interface**: Define as a pure virtual interface in C++.
*   **Threading**: Callbacks are always delivered on the UI thread.

## Implementation Risks
*   **Coordinate Math**: Implementations must correctly subtract the "Scroll Delta" to map the global capture request to local view coordinates.
*   **Buffer Management**: Failing to signal completion via the `onComplete` consumer will hang the screenshot tool.
