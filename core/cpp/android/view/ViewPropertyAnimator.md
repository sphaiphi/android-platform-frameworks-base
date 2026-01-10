# ViewPropertyAnimator - Reverse Engineering Documentation

## Executive Summary
`ViewPropertyAnimator` provides a fluent, optimized API for animating a specific set of properties on a `View` (Translation, Scale, Rotation, Alpha). it differs from `ObjectAnimator` by batching multiple property changes into a single internal `ValueAnimator`, which reduces the number of invalidation calls and improves performance.

## Architecture Overview
*   **Role**: Fluent View animator.
*   **Retrieval**: Accessed via `view.animate()`.
*   **Mechanism**: Uses a single `ValueAnimator` that runs from 0 to 1, then interpolates all requested properties based on their delta values.

## Detailed Functionality

### 1. Fluent Interface
*   Supports chaining: `view.animate().x(100).y(100).alpha(0.5).setDuration(500).start()`.

### 2. Optimization
*   **Batching**: Combines all property requests made in a single execution cycle (via a posted `Runnable`) into one animation.
*   **Hardware Acceleration**: `withLayer()` automatically switches the view to a hardware layer for the duration of the animation.

### 3. Lifecycle Hooks
*   **`withStartAction()`** / **`withEndAction()`**: Convenient callbacks for choreographing complex sequences.

## Java-to-C++ Translation Guide
*   **Pattern**: Builder Pattern / Command Pattern.
*   **Interpolation**: Map to native `android::uirenderer::RenderNode` updates if hardware-accelerated.

## Implementation Risks
*   **Overlapping Animations**: If a property is already animating when a new request arrives, the old animation for that property is cancelled to prevent conflicts.
*   **Reference Leaks**: The internal `Handler` and `Runnable` must be carefully managed to avoid keeping `View` objects alive longer than their window lifecycle.
