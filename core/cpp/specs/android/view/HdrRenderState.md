# HdrRenderState - Reverse Engineering Documentation

## Executive Summary
`HdrRenderState` manages the transition and scaling of HDR (High Dynamic Range) content within a `ViewRootImpl`. It tracks the desired HDR/SDR ratio and handles smooth animations when switching between SDR and HDR rendering states to prevent abrupt jumps in screen brightness.

## Architecture Overview
*   **Role**: HDR brightness animator.
*   **Listener**: Implements `Consumer<Display>` to react to system-wide HDR/SDR ratio changes.
*   **Target**: Updates the `HardwareRenderer` via `ViewRootImpl`.

## Detailed Functionality

### 1. State Tracking
*   **Desired Ratio**: The ideal brightness boost requested by the content.
*   **Render Ratio**: The actual ratio currently being applied to the hardware compositor.

### 2. Animation
*   **`updateForFrame()`**: Calculates the "step" for the current frame based on elapsed time (`TRANSITION_PER_MS`). It ensures the brightness ramps up or down smoothly over several hundred milliseconds.

### 3. Display Integration
*   **`forceUpdateHdrSdrRatio()`**: Synchronizes the local target with the display's current capabilities.

## Java-to-C++ Translation Guide
*   **Timing**: Requires access to `SystemClock.uptimeMillis()` or a native high-precision monotonic clock.
*   **Invalidation**: Triggers `ViewRootImpl.invalidate()` to keep the animation loop running.

## Implementation Risks
*   **Battery Impact**: Extended HDR rendering consumes significantly more power. The render state must strictly follow the "HDR Enabled" flag.
*   **Visual Jumps**: If the frame time delta is too large, the transition might appear jerky. The logic clamps the time delta to a maximum of 32ms.
