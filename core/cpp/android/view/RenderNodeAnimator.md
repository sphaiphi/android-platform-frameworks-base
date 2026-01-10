# RenderNodeAnimator - Reverse Engineering Documentation

## Executive Summary
`RenderNodeAnimator` is a high-performance animator that executes directly on the hardware "RenderThread." Unlike standard `ValueAnimator` or `ObjectAnimator` which update properties on the UI thread and trigger a full view invalidation, `RenderNodeAnimator` modifies the properties of a `RenderNode` (e.g., translation, scale, alpha) in the background, ensuring smooth 60fps/120fps animations even when the UI thread is busy.

## Architecture Overview
*   **Role**: Hardware-accelerated property animator.
*   **Target**: Operates on a `RenderNode` rather than a `View`.
*   **Threading**: Configured on the UI thread, but the actual interpolation and frame updates occur on the `RenderThread`.

## Detailed Functionality

### 1. Property Animation
*   Supports animating standard properties like `ALPHA`, `TRANSLATION_X/Y/Z`, `SCALE_X/Y`, and `ROTATION`.
*   Also supports `CanvasProperty` animations, which allow for low-level drawing parameter changes (like paint color or stroke width) without triggering Java-side updates.

### 2. Synchronization
*   **`onAlphaAnimationStart()`**: Specially handles alpha, as the canonical alpha value is often stored in both the `RenderNode` and the `View`. It ensures the `View`'s internal state matches the hardware target.
*   **`invalidateParent()`**: Triggers a minimal redraw signal to the parent view hierarchy to ensure the animating node is correctly composited.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Maps directly to `android::uirenderer::BaseRenderNodeAnimator`.
*   **Interpolation**: Uses a native `TimeInterpolator` (e.g., `LinearInterpolator`, `AccelerateDecelerateInterpolator`) implemented in C++.

## Implementation Risks
*   **State Desync**: Since the animation runs on a separate thread, the Java `View` properties may not reflect the "current" hardware state until the animation finishes or a sync point is reached.
*   **One-Shot Lifecycle**: RenderNodeAnimators are generally one-shot; they cannot be easily reversed or re-played without re-initialization.
