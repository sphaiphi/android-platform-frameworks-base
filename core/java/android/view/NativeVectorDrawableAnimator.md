# NativeVectorDrawableAnimator - Reverse Engineering Documentation

## Executive Summary
`NativeVectorDrawableAnimator` is an internal interface that provides a bridge between `android.graphics` (where Vector Drawables reside) and `android.view` (where the rendering pipeline resides). it allows for animations of Vector Drawables to be executed directly on the hardware `ThreadedRenderer`.

## Architecture Overview
*   **Role**: Cross-package animation bridge.
*   **Integration**: Used by `ViewAnimationHostBridge` to register animators with the `ViewRootImpl`.

## Detailed Functionality
*   **`getAnimatorNativePtr()`**: Returns the raw memory address of the C++ animator object.
*   **`setThreadedRendererAnimatorListener()`**: Sets a callback to be notified of animation lifecycle events on the render thread.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: This interface maps to the native `android::uirenderer::BaseRenderNodeAnimator` subclasses specifically for vector properties.

## Implementation Risks
*   **Unsafe Pointers**: Handling raw `long` pointers requires extreme caution. The native object's lifecycle must be strictly managed to prevent use-after-free crashes.
