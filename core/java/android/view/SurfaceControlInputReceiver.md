# SurfaceControlInputReceiver - Reverse Engineering Documentation

## Executive Summary
`SurfaceControlInputReceiver` is an interface that provides a mechanism for a specific `SurfaceControl` (compositor layer) to receive input events directly, bypassing the standard window-based dispatch if needed. this is a modern, flexible alternative to the traditional `IWindow`-based input model.

## Architecture Overview
*   **Role**: Direct layer input consumer.
*   **Event Model**: Supports both batched (per-frame) and unbatched (immediate) event delivery.

## Detailed Functionality
*   **`onInputEvent()`**: The primary callback. The `InputEvent` provided is recycled immediately after the call returns, requiring the implementer to copy it if needed asynchronously.

## Java-to-C++ Translation Guide
*   **Integration**: In C++, this corresponds to a callback registered with the `InputReceiver` for a specific layer.
*   **Parceling**: Closely tied to the `InputTransferToken` system for secure focus management.

## Implementation Risks
*   **Event Lifecycle**: The aggressive recycling of input events (`onInputEvent` returning) can lead to crashes if an app attempts to use the event on a background thread without copying it.
