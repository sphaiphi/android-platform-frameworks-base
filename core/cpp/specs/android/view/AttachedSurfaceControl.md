# AttachedSurfaceControl - Reverse Engineering Documentation

## Executive Summary
`AttachedSurfaceControl` provides an interface to the root `SurfaceControl` of a view hierarchy or window. It allows applications to attach their own custom `SurfaceControl` layers to the app's window and perform surface transactions synchronized with the UI thread's drawing cycle.

## Architecture Overview
*   **Role**: Synchronization bridge for app-created surfaces.
*   **Threading**: Annotated with `@UiThread`, meaning all methods must be called from the thread that owns the window.
*   **Retrieval**: Obtained via `View.getRootSurfaceControl()` or `Window.getRootSurfaceControl()`.

## Detailed Functionality

### 1. Surface Integration
*   **`buildReparentTransaction(SurfaceControl)`**: Creates a transaction to make a custom surface a child of the window's root surface.
*   **`applyTransactionOnDraw(Transaction)`**: Merges a surface transaction into the next frame's draw cycle, ensuring zero-latency updates between View changes and Surface changes.

### 2. Rendering Hints
*   **`getBufferTransformHint()`**: Provides info on how the composer expects buffers to be rotated (e.g., for landscape-only hardware).

### 3. Jank and Performance
*   **`registerOnJankDataListener()`**: Allows the app to receive feedback from the compositor about frame drops and scheduling misses.

## Java-to-C++ Translation Guide
*   **Interface**: In C++, this should be a virtual interface implemented by the `ViewRootImpl` equivalent.
*   **Transaction Sync**: Link directly to `android::SurfaceComposerClient::Transaction`.

## Implementation Risks
*   **Deadlocks**: Since transactions are applied "on draw," poorly managed native transactions can block the UI thread.
*   **Coordinate Confusion**: `setChildBoundingInsets` uses window-space coordinates, which may differ from surface-local coordinates.
