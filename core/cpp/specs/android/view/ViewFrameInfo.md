# ViewFrameInfo - Reverse Engineering Documentation

## Executive Summary
`ViewFrameInfo` is an internal utility class that tracks timing and metadata for a single frame within `ViewRootImpl`. it is used to populate the lower-level `FrameInfo` structure used by the hardware rendering pipeline for performance monitoring and jank tracking.

## Data Model
*   **`drawStart`**: `long` - The timestamp when the draw phase began.
*   **`flags`**: `long` - Metadata about the frame state (e.g., `FLAG_WINDOW_LAYOUT_CHANGED`).
*   **`mInputEventId`**: `int` - The identifier of the input event that triggered this frame.

## Detailed Functionality
*   **`populateFrameInfo()`**: Transfers the local Java data into the raw `long[]` array used by the native `HardwareRenderer`.
*   **`reset()`**: Clears the frame state for the next traversal cycle.

## Java-to-C++ Translation Guide
*   **Native Link**: Directly associated with `android::uirenderer::FrameInfoIndex` in the HWUI library.

## Implementation Risks
*   **Sync Errors**: If the input event ID is not correctly associated with the frame, latency calculations in `dumpsys gfxinfo` will be incorrect.
