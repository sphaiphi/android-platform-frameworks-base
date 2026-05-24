# FullscreenRequestHandler - Reverse Engineering Documentation

## Executive Summary
`FullscreenRequestHandler` handles requests from activities to enter or exit fullscreen mode (specifically for multi-window/desktop environments).

## Architecture Overview
*   **Usage**: Static helper.
*   **Dependencies**: `ActivityClient`.

## Detailed Functionality
*   **Validation**: Checks if request matches windowing mode (e.g., requesting exit when not fullscreen).
*   **Execution**: Calls `ActivityClient.requestMultiwindowFullscreen`.
*   **Callback**: Reports result via `OutcomeReceiver`.

## Java-to-C++ Translation Guide
*   Logic helper.

## Implementation Risks
*   None.
