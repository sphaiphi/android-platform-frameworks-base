# SyncRtSurfaceTransactionApplier - Reverse Engineering Documentation

## Executive Summary
`SyncRtSurfaceTransactionApplier` is a utility used to apply `SurfaceControl.Transaction` operations in perfect synchronization with the hardware "RenderThread." It ensures that modifications to compositor layers (position, alpha, crop) are committed to the display at the exact same time as the UI thread's view updates.

## Architecture Overview
*   **Role**: Surface-to-View sync orchestrator.
*   **Mechanism**: Uses `registerRtFrameCallback` on the `ViewRootImpl` to schedule native transactions.
*   **Data Unit**: `SurfaceParams` - a descriptor of all modifications to be applied to a single surface.

## Detailed Functionality

### 1. Parameter Bundling (`SurfaceParams`)
*   Encapsulates flags for `ALPHA`, `MATRIX`, `WINDOW_CROP`, `LAYER`, `CORNER_RADIUS`, `VISIBILITY`, and `OPAQUE`.
*   Supports merging an existing `Transaction` into the sync cycle.

### 2. Scheduling (`scheduleApply`)
*   Captures the current `SurfaceControl` from the `ViewRootImpl`.
*   Registers a native callback that fires during the RenderThread's next frame processing.

### 3. Execution (`applyParams`)
*   (Static method) Unpacks the `SurfaceParams` and applies them to a raw native `android::SurfaceControl::Transaction`.

## Java-to-C++ Translation Guide
*   **Sync Logic**: In C++, this integrates with `android::uirenderer::CanvasContext::addFrameMetricsObserver` or similar RenderThread frame hooks.
*   **Transaction Parity**: Directly maps to the native `SurfaceComposerClient::Transaction` API.

## Implementation Risks
*   **UI Thread Invalidation**: To ensure the scheduled transaction actually runs, the applier must force an invalidation of the anchor view (`targetView.invalidate()`).
*   **State Conflict**: If multiple appliers or different transaction mechanisms modify the same surface, the final visual result depends on the order of the RenderThread work queue.
