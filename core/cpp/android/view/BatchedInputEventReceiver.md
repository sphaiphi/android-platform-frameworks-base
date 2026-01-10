# BatchedInputEventReceiver - Reverse Engineering Documentation

## Executive Summary
`BatchedInputEventReceiver` is a specialized `InputEventReceiver` that optimizes input processing by batching multiple motion events (like touch moves) and delivering them only once per display frame (aligned with VSync). This reduces the overhead of processing high-frequency sensor data on the UI thread.

## Architecture Overview
*   **Role**: High-frequency input optimizer.
*   **Dependency**: `Choreographer` - uses VSync signals to trigger the consumption of batched events.
*   **Logic**: Instead of processing every `MotionEvent` immediately, it queues them and processes the latest state during the "Input" stage of the frame pipeline.

## Detailed Functionality

### 1. Batching Logic
*   **`onBatchedInputEventPending()`**: Called when the system has input samples ready. If batching is enabled, it schedules a callback via `Choreographer`.
*   **`doConsumeBatchedInput()`**: Triggered by the `Choreographer`. It calls `consumeBatchedInputEvents` with the current frame time.

### 2. Lifecycle
*   **`setBatchingEnabled(boolean)`**: Allows toggling between immediate delivery and batched delivery. Disabling batching flushes all pending events immediately.

## Java-to-C++ Translation Guide
*   **Native Link**: Wraps the native `InputEventReceiver`'s batching capabilities.
*   **VSync Sync**: Ensure integration with the native `Choreographer` (based on `DisplayEventReceiver`).

## Implementation Risks
*   **Latency**: Batching inherently adds a small amount of latency (up to one frame) to improve throughput.
*   **Starvation**: If the UI thread is too busy to process frames, input events can accumulate, potentially causing the input buffer to fill up.
