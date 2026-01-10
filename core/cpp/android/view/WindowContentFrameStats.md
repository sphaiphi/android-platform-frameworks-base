# WindowContentFrameStats - Reverse Engineering Documentation

## Executive Summary
`WindowContentFrameStats` provides detailed rendering statistics for a specific window's content (e.g., during scrolling). it tracks when frames were posted by the app, when they were ready for display (GPU work finished), and when they were actually presented on screen.

## Data Model
*   **`mFramesPostedTimeNano`**: When the app committed the frame.
*   **`mFramesReadyTimeNano`**: When the GPU finished rendering the frame.
*   **`mFramesPresentedTimeNano`**: When the display hardware showed the frame.

## Detailed Functionality
*   **Jank Analysis**: By comparing these three arrays, the system can determine if a frame drop was caused by the application (slow `onDraw`) or the system (slow compositor).

## Java-to-C++ Translation Guide
*   **Native Link**: Populated by the `HardwareRenderer` in native code.

## Implementation Risks
*   **Buffer Alignment**: The arrays must stay perfectly aligned by frame index to ensure valid latency calculations.
