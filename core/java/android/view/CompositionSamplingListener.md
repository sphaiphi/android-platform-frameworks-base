# CompositionSamplingListener - Reverse Engineering Documentation

## Executive Summary
`CompositionSamplingListener` allows applications to sample the result of the screen composition (the final pixels shown on the display) within a specific area. It is primarily used to determine the median luminance (brightness) of a region, which can be useful for adjusting the color of UI elements (e.g., adaptive icons or text) to maintain contrast.

## Architecture Overview
*   **Role**: Screen content analysis utility.
*   **Source**: Receives data from SurfaceFlinger via a native listener.
*   **Threading**: Callbacks are dispatched from a binder thread onto a user-supplied `Executor`.

## Detailed Functionality

### 1. Registration
*   **`register(listener, displayId, stopLayer, samplingArea)`**: Subscribes to sampling for a specific area. The `stopLayer` can be used to exclude certain layers from the sample.
*   **`samplingArea`**: A `Rect` defining the region in screen coordinates to analyze.

### 2. Data Reporting
*   **`onSampleCollected(float medianLuma)`**: The primary callback. Returns a value representing the median brightness of the sampled area.

## Java-to-C++ Translation Guide
*   **Native Linkage**: The class is a wrapper around a native C++ object. In C++, implement a subclass of `android::CompositionSamplingListener`.
*   **IPC**: Uses a dedicated Binder interface for SurfaceFlinger callbacks.

## Implementation Risks
*   **Performance**: Sampling happens continuously as frames are composed. Excessive listeners or large sampling areas can impact the performance of SurfaceFlinger.
*   **Privacy**: Access to screen content is sensitive. This API is restricted and typically used only for specific system UI behaviors.
