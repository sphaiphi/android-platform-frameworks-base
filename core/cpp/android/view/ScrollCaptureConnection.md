# ScrollCaptureConnection - Reverse Engineering Documentation

## Executive Summary
`ScrollCaptureConnection` acts as a mediator between a `ScrollCaptureCallback` (implemented by a view) and a remote process (usually the system screenshot tool). it coordinates the start of a capture session, requests for specific image regions, and the eventual teardown of the connection.

## Architecture Overview
*   **Role**: Cross-process scroll capture coordinator.
*   **Communication**: Implements `IScrollCaptureConnection` (Binder interface).
*   **Threading**: Proxies remote binder calls onto the application's UI thread for safe view interaction.

## Detailed Functionality

### 1. Session Lifecycle
*   **`startCapture()`**: Links the remote screenshot tool to the local view hierarchy. It creates a `ScrollCaptureSession` and triggers the view's `onScrollCaptureStart`.
*   **`endCapture()`**: Signals that the capture is complete and the view should return to its normal state.

### 2. Image Requests
*   **`requestImage(Rect)`**: Requests the view to render a specific area of its scrollable content into the provided `Surface`.

### 3. Safety and Robustness
*   **`SafeCallback`**: Ensures that callbacks are only delivered once and are ignored if the operation was cancelled.
*   **Death Recipient**: Automatically cleans up if the remote controlling process crashes.

## Java-to-C++ Translation Guide
*   **IPC**: Implement as a subclass of `BnScrollCaptureConnection`.
*   **Trace**: Extensive usage of `ATRACE` for debugging capture latency.

## Implementation Risks
*   **UI Blocking**: Since image requests are handled on the UI thread, complex rendering can stall the app.
*   **Cancellation**: Correctly handling the `ICancellationSignal` is vital to prevent rendering work for requests that are no longer needed.
