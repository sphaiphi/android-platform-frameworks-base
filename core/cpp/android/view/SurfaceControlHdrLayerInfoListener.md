# SurfaceControlHdrLayerInfoListener - Reverse Engineering Documentation

## Executive Summary
`SurfaceControlHdrLayerInfoListener` allows for the monitoring of HDR (High Dynamic Range) content across different displays. it provides callbacks when the number of visible HDR layers changes, along with metadata about their dimensions and the maximum desired HDR/SDR brightness ratio.

## Architecture Overview
*   **Role**: Display-specific HDR monitor.
*   **Context**: Primarily used by the system to adjust display brightness or tone mapping when HDR content is present.
*   **IPC**: Registers with the system server via a native handle.

## Detailed Functionality
*   **`onHdrInfoChanged()`**: Reports the display token, number of HDR layers, the dimensions of the largest HDR layer, and the `maxDesiredHdrSdrRatio`.
*   **`register(IBinder displayToken)`**: Scopes the listener to a specific physical or logical display.

## Java-to-C++ Translation Guide
*   **Native Link**: Connects to the native `HdrLayerInfoReporter` in SurfaceFlinger.
*   **Precision**: HDR/SDR ratios are handled as `float`.

## Implementation Risks
*   **Security**: Requires the `CONTROL_DISPLAY_BRIGHTNESS` permission.
*   **Coordinate Drift**: Dimension reporting (`maxW`, `maxH`) must correctly account for display scaling and rotation.
