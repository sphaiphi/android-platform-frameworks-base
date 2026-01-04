# ZoomButton - Reverse Engineering Documentation

## Executive Summary
`ZoomButton` is a deprecated widget that fires click events repeatedly while pressed. It was intended for zooming but is just a generic "repeat listener" button.

## Architecture Overview
*   **Inheritance**: `ImageButton` -> `ZoomButton`.
*   **Status**: Deprecated.

## Detailed Functionality
*   **Long Press**: On long click, starts a runnable that calls `callOnClick()` repeatedly.
*   **Speed**: `setZoomSpeed` controls the frequency.

## Java-to-C++ Translation Guide
*   **Logic**: Repeat timer logic.

## Implementation Risks
*   None.
