# ThreadedRenderer - Reverse Engineering Documentation

## Executive Summary
`ThreadedRenderer` is the primary entry point for the hardware-accelerated rendering pipeline in an application process. It proxies rendering calls from the UI thread to a dedicated "RenderThread." It manages the lifecycle of the EGL/Vulkan context, the `RenderNode` tree, and the synchronization of "DisplayLists" between the two threads.

## Architecture Overview
*   **Role**: UI-to-Hardware rendering bridge.
*   **Hierarchy**: Inherits from `HardwareRenderer`.
*   **Threading**: Manages the critical handshake where the UI thread records drawing commands and the RenderThread executes them on the GPU.

## Detailed Functionality

### 1. Traversal Integration
*   **`draw(View, AttachInfo, Callbacks)`**: The main draw loop. It records the view tree into a root `RenderNode` DisplayList and then triggers `syncAndDrawFrame()`.

### 2. Hardware Resource Management
*   **`initialize()`** / **`updateSurface()`**: Links the renderer to a physical `Surface`.
*   **`destroyHardwareResources()`**: Cleans up GPU-side buffers and textures when a window is hidden or detached.

### 3. Profiling and Debugging
*   Handles system properties like `debug.hwui.profile` to output frame timing data to `dumpsys gfxinfo`.

## Java-to-C++ Translation Guide
*   **Native Link**: Directly wraps the native `android::uirenderer::renderthread::RenderProxy`.
*   **Pipeline**: Orchestrates the `android::uirenderer::CanvasContext`.

## Implementation Risks
*   **Sync Stall**: If the RenderThread is blocked (e.g., by a slow GPU driver or heavy shaders), the UI thread will stall during the sync phase, leading to ANRs.
*   **Context Loss**: Must gracefully handle "Lost Surface" errors by forcing a full window relayout.
