# SurfaceControl - Reverse Engineering Documentation

## Executive Summary
`SurfaceControl` is a low-level handle to a layer in the system's screen compositor (SurfaceFlinger). While a `Surface` is used for content production (drawing), `SurfaceControl` manages the metadata of how that content is displayed: its Z-order, visibility, position, transformation matrix, cropping, and alpha blending. It is the fundamental primitive for the "Scene Graph" managed by the Window Manager.

## Architecture Overview
*   **Role**: Metadata and hierarchy controller for composition layers.
*   **Hierarchy**: SurfaceControls are arranged in a tree. Geometric properties (transform, alpha) are inherited from parents.
*   **IPC**: Native handle (`mNativeObject`) represents a `sp<SurfaceControl>` in the system process.
*   **Transactions**: All modifications are batched into `SurfaceControl.Transaction` objects, which are applied atomically.

## Detailed Functionality

### 1. Creation and Lifecycle
*   **`SurfaceControl.Builder`**: Used to create a new layer. Specifies name, size, format, and flags (`HIDDEN`, `OPAQUE`, `SECURE`).
*   **`release()`**: Frees the native handle and associated server-side resources.

### 2. The Transaction API
Modifications to one or more surfaces are performed via a `Transaction`:
*   **`setLayer(int)`**: Controls Z-order.
*   **`setPosition(float, float)`** / **`setScale(float, float)`**: Controls layout.
*   **`setMatrix()`**: Applies complex transformations (rotation, skew).
*   **`setAlpha(float)`**: Controls transparency.
*   **`reparent(SurfaceControl)`**: Moves a surface to a new parent in the hierarchy.

### 3. Modern Buffer Management (BLAST)
*   Modern Android uses "BLAST" (Buffer-Life-And-Sync-Transactions). `SurfaceControl` can directly accept buffers via `setBuffer(HardwareBuffer)`, allowing for perfectly synchronized updates between geometry changes and buffer submission.

### 4. Hardware Integration
*   **`SECURE`**: Prevents screenshots or mirroring.
*   **`setCornerRadius()`**: Applies hardware-accelerated rounded corners.
*   **`setBackgroundBlurRadius()`**: Triggers GPU-based background blurring.

## Java-to-C++ Translation Guide
*   **Primary Mapping**: Wrap `android::SurfaceControl`.
*   **Atomic Updates**: Use `android::SurfaceComposerClient::Transaction`.
*   **Native Handles**: The Java `mNativeObject` is a `long` holding the raw pointer to the C++ object. Ensure `NativeAllocationRegistry` or manual `release` handles the lifecycle.

## Implementation Risks
*   **Transaction Performance**: Excessive atomic transactions can overwhelm SurfaceFlinger.
*   **Resource Leaks**: Abandoned `SurfaceControl` objects keep buffers and layers alive in the compositor process, leading to severe system-wide memory pressure.
*   **Sync Complexity**: Coordinating transactions between multiple processes (e.g., App and SystemUI) requires using `SurfaceSyncGroup` or similar synchronization primitives.
