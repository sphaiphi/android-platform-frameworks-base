# FrameMetricsObserver - Reverse Engineering Documentation

## Executive Summary
`FrameMetricsObserver` is a helper class that implements the `HardwareRendererObserver.OnFrameMetricsAvailableListener` interface. It provides a bridge between the low-level hardware renderer and the application-level `Window.OnFrameMetricsAvailableListener`.

## Architecture Overview
*   **Role**: Rendering performance stream mediator.
*   **Dependency**: `HardwareRendererObserver` - the underlying engine that listens to the native rendering pipeline.
*   **Reference**: Holds a `WeakReference<Window>` to ensure it doesn't prevent window cleanup.

## Detailed Functionality
*   **`onFrameMetricsAvailable(int dropCount)`**: Receives the signal from the hardware renderer that a new batch of timing data is ready. It then forwards the `FrameMetrics` object to the registered application listener.

## Java-to-C++ Translation Guide
*   **Native Link**: Connects to the native `FrameInfo` observer in the HWUI library.
*   **Callback**: In C++, this would be implemented as a callback registered with the `CanvasContext`.

## Implementation Risks
*   **Callback Latency**: If the application's listener is slow, it may drop reports.
*   **Threading**: Callbacks occur on the thread associated with the `Handler` passed to the constructor.
