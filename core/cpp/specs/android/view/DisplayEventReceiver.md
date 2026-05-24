# DisplayEventReceiver - Reverse Engineering Documentation

## Executive Summary
`DisplayEventReceiver` is a low-level utility class used to receive display events, primarily vertical synchronization (VSync) signals and configuration changes, from the system compositor (SurfaceFlinger). It is the foundational component for the `Choreographer`'s frame timing system.

## Architecture Overview
*   **Role**: VSync and Display Event consumer.
*   **JNI Centric**: Acts as a Java wrapper around a native C++ `DisplayEventReceiver`.
*   **Threading**: MUST be used on a `Looper` thread. It registers with the thread's `MessageQueue` to receive file descriptor events from SurfaceFlinger.
*   **Source Types**:
    *   `VSYNC_SOURCE_APP`: Standard VSync for application rendering.
    *   `VSYNC_SOURCE_SURFACE_FLINGER`: VSync used by the compositor itself.

## Detailed Functionality

### 1. Event Callbacks
*   **`onVsync()`**: Called when a VSync pulse occurs. Provides timestamps and VSync IDs.
*   **`onHotplug()`**: Triggered when a physical display is connected or disconnected.
*   **`onModeChanged()`**: Triggered when the display refresh rate or resolution changes.

### 2. Control
*   **`scheduleVsync()`**: Requests a single VSync pulse from SurfaceFlinger. This is called repeatedly by `Choreographer` to drive the animation loop.

## Java-to-C++ Translation Guide
*   **Native Link**: Directly wraps `android::DisplayEventReceiver`.
*   **Event Loop**: In C++, use `ALooper_addFd` to listen for events on the DisplayEventReceiver's data pipe.
*   **Parceling**: Not typically parceled; used as a local handle to a system connection.

## Implementation Risks
*   **Thread Safety**: The receiver is NOT thread-safe. All calls must be serialized on the associated `Looper`.
*   **Starvation**: If the `Looper` thread is blocked, VSync events will queue up, leading to jank or missed frames.
*   **Resource Leak**: Failure to call `dispose()` results in an open file descriptor and a pending native allocation.
