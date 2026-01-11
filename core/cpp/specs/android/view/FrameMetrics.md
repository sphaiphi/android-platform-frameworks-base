# FrameMetrics - Reverse Engineering Documentation

## Executive Summary
`FrameMetrics` provides precise timing data for the various milestones in a single frame's lifecycle. It allows applications to measure their own rendering performance (jank detection) by exposing timestamps from the hardware rendering subsystem.

## Data Model

### Metric Identifiers
*   **`UNKNOWN_DELAY_DURATION`**: Time spent waiting for the UI thread to become responsive.
*   **`INPUT_HANDLING_DURATION`**: Time spent in `onTouchEvent`, etc.
*   **`ANIMATION_DURATION`**: Time spent executing `Animator` callbacks.
*   **`LAYOUT_MEASURE_DURATION`**: Time spent in `onMeasure` and `onLayout`.
*   **`DRAW_DURATION`**: Time spent recording `DisplayList`s.
*   **`SYNC_DURATION`**: Time spent uploading resources to the GPU.
*   **`COMMAND_ISSUE_DURATION`**: Time spent issuing draw calls to the GPU driver.
*   **`TOTAL_DURATION`**: End-to-end time from VSync to frame completion.

## Detailed Functionality
*   **`getMetric(int id)`**: Retrieves the duration in nanoseconds for a specific milestone.
*   **Data Source**: Wraps a `long[]` array (`mTimingData`) which is populated by the native `HardwareRenderer`.

## Java-to-C++ Translation Guide
*   **Native Link**: Directly associated with `android::uirenderer::FrameInfo`.
*   **Timestamps**: Use `CLOCK_MONOTONIC` or equivalent high-precision timer.

## Implementation Risks
*   **Overhead**: While designed to be lightweight, collecting metrics for every frame can add minor overhead.
*   **Staleness**: The metrics for a frame are only available after the frame has been fully processed by the RenderThread.
