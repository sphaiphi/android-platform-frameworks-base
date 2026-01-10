# SharedElementCallback - Reverse Engineering Documentation

## Executive Summary
`SharedElementCallback` provides hooks for monitoring and customizing shared element transitions during activity or fragment transitions. It allows developers to adjust the starting and ending states of shared views, handle rejected elements, and manage snapshots of views during the transition process. It is key for implementing high-quality "Hero" animations in Android apps.

## Architecture Overview
- **Structure**: Abstract class with optional hooks for various stages of the transition.
- **Key Stages**:
    - `onSharedElementStart`: Captured before the transition begins.
    - `onSharedElementEnd`: Captured when the transition concludes.
    - `onMapSharedElements`: Adjusts the mapping of transition names to actual views.
    - `onRejectSharedElements`: Handles views that were not part of the destination hierarchy.
- **Snapshot Support**: Includes logic for capturing and recreating view snapshots (bitmaps or hardware buffers).

## Detailed Functionality

### Snapshot Capture (`onCaptureSharedElementSnapshot`)
**Purpose**: Creates a portable representation of a view to be used in another window.
**Logic**:
1. If the view is an `ImageView`, it extracts the bitmap directly if possible.
2. Otherwise, it uses `TransitionUtils.createViewBitmap` to render the view into a bitmap based on its global matrix and screen bounds.
3. Supports `HardwareBuffer` for optimized GPU-side data transfer.

### Snapshot Restoration (`onCreateSnapshotView`)
**Purpose**: Reconstitutes a snapshot into a visible `View`.
**Algorithm**:
1. Decodes the `Parcelable` snapshot (either a `Bitmap` or a `Bundle` with `HardwareBuffer`).
2. If it's a bundle, it creates an `ImageView` and configures its scale type and matrix to match the original view.
3. If it's a simple bitmap, it creates a `View` with the bitmap as its background.

### Async Coordination (`onSharedElementsArrived`)
**Purpose**: Allows destination activities to delay the transition until shared elements are ready (e.g., loaded from the network).
**Mechanism**: Provides a `listener` that the app must call (`onSharedElementsReady()`) to trigger the actual transfer.

## API Reference
- `public void onSharedElementStart(...)`: Start state hook.
- `public void onSharedElementEnd(...)`: End state hook.
- `public Parcelable onCaptureSharedElementSnapshot(...)`: Data capture.
- `public View onCreateSnapshotView(...)`: View reconstruction.

## Java-to-C++ Translation Guide
- **Bitmap Management**: Map Java's `Bitmap` and `HardwareBuffer` to `android::graphics::Bitmap` and `AHardwareBuffer` in C++.
- **View Hierarchy**: Port the snapshot view creation logic to a native UI framework.
- **Matrix Math**: Use `android::graphics::Matrix` for coordinate space transformations.

## Implementation Risks
- **Hardware Buffers**: Correctly managing the lifecycle of `HardwareBuffer` objects across process boundaries is critical to avoid crashes or memory corruption.
- **Layout Timing**: `onSharedElementStart` is called without a layout pass occurring immediately after. C++ implementation must ensure view properties are applied correctly before the next frame.
- **Visual Consistency**: The logic for `ScaleType.MATRIX` and complex image transformations must be perfectly replicated to avoid "jumping" animations.
