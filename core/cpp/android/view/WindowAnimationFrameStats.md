# WindowAnimationFrameStats - Reverse Engineering Documentation

## Executive Summary
`WindowAnimationFrameStats` provides timing data for system-level window animations (e.g., activity transitions). it captures a snapshot of frame presentation times over a specific interval to help the system monitor the smoothness of UI transitions.

## Data Model
*   **`mRefreshPeriodNano`**: The system's target frame duration.
*   **`mFramesPresentedTimeNano`**: Array of actual presentation timestamps for the animation.

## Detailed Functionality
*   **Deprecated**: This class is largely superseded by modern Perfetto-based `FrameTimeline` metrics.

## Java-to-C++ Translation Guide
*   **Mapping**: Map to a C++ `struct`.
*   **Parceling**: Serialize the refresh period followed by the long array.

## Implementation Risks
*   **Data Resolution**: Ensure timestamps are recorded using the same clock as the rendering pipeline (`CLOCK_MONOTONIC`).
