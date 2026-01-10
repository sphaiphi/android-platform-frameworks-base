# Choreographer - Reverse Engineering Documentation

## Executive Summary
`Choreographer` coordinates the timing of animations, input, and drawing within an application. It receives periodic timing pulses (vertical synchronization, or VSync) from the display subsystem and schedules work to occur at the start of the next display frame. It ensures that the UI remains smooth and synchronized with the physical refresh rate of the screen.

## Architecture Overview
*   **Role**: Timing and synchronization engine.
*   **Threading**: Thread-local singleton. Each thread with a `Looper` has its own `Choreographer`. The main UI thread's choreographer is the most significant.
*   **Source**: Receives events from `DisplayEventReceiver` (which links to SurfaceFlinger's VSync signals).
*   **Work Pipeline**: Work is categorized into stages (Input, Animation, Insets, Traversal, Commit) and executed in that strict order during each frame.

## Detailed Functionality

### 1. Frame Callbacks
*   **`postFrameCallback()`**: Allows an app to run code once at the start of the next frame. Used extensively by the animation and View systems.
*   **`postVsyncCallback()`**: A more modern variation for precise VSync-aligned work.

### 2. The Frame Loop (`doFrame`)
When a VSync pulse arrives:
1.  **Calculate Jitter**: Checks if the frame is starting later than intended (jank detection).
2.  **Input Stage**: Processes queued touch and key events.
3.  **Animation Stage**: Updates animator values (e.g., `ValueAnimator`).
4.  **Insets Animation Stage**: Specifically handles window inset changes (IME, system bars).
5.  **Traversal Stage**: Triggers the `ViewRootImpl` to perform measure, layout, and draw.
6.  **Commit Stage**: Finalizes the frame state.

### 3. Frame Data
*   **`FrameTimeline`**: Provides the intended and expected presentation times for the current and future frames, allowing the renderer to adjust for potential latency.

## Java-to-C++ Translation Guide
*   **VSync Linkage**: Use `android::DisplayEventReceiver` to receive native VSync signals.
*   **Thread Affinity**: Implement using a per-thread event loop (like `ALooper`).
*   **Priority**: Work scheduled via Choreographer should be treated as high priority to avoid frame drops.

## Implementation Risks
*   **Jank**: If any callback in the chain (Input, Animation, Traversal) takes longer than the frame interval (e.g., 16.6ms for 60Hz), the frame is dropped, causing a visible skip.
*   **Callback Flooding**: Posting too many runnables can overwhelm the message queue.
*   **Misaligned Timings**: Using `System.currentTimeMillis()` for animations instead of the `frameTime` provided by Choreographer leads to inconsistent and "jerky" motion.
