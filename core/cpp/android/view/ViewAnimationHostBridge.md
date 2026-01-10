# ViewAnimationHostBridge - Reverse Engineering Documentation

## Executive Summary
`ViewAnimationHostBridge` acts as a connector between a `View` and its associated `RenderNode`'s animation hosting logic. it ensures that hardware-accelerated animators (like `RenderNodeAnimator`) are correctly registered with the `ViewRootImpl` and that the view is kept in a "drawn" state while an animation is active.

## Architecture Overview
*   **Role**: UI-to-RenderThread animation bridge.
*   **Interface**: Implements `RenderNode.AnimationHost`.
*   **Mechanism**: Monitors animation lifecycle (`onAnimationStart/End`) to inform the `ViewRootImpl` about active threaded animations.

## Detailed Functionality
*   **`registerAnimatingRenderNode()`**: Forwards the animation request to the `ViewRootImpl`.
*   **`registerVectorDrawableAnimator()`**: Specifically handles vector-based hardware animations.

## Java-to-C++ Translation Guide
*   **Integration**: In C++, this component resides in the handshake between `android::uirenderer::RenderNode` and `android::view::ViewRootImpl`.

## Implementation Risks
*   **Dangling References**: The bridge must ensure the `View` is still attached (`isAttached()`) before attempting to register an animation.
