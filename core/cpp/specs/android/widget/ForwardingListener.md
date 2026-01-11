# ForwardingListener - Reverse Engineering Documentation

## Executive Summary
`ForwardingListener` is a complex `OnTouchListener` implementation used to forward touch events from a source view (anchor) to a popup window (target), enabling "drag-to-open" behavior (e.g., touching a spinner and dragging directly to an item in the dropdown).

## Architecture Overview
*   **Inheritance**: `View.OnTouchListener`.
*   **Role**: Touch Event Proxy.

## Detailed Functionality
*   **Long Press / Tap**: Detects if the user is holding down or tapping.
*   **Forwarding**: If conditions are met, it takes subsequent `MotionEvent`s, transforms coordinates to the target popup's local space, and injects them into the popup's view.
*   **Parent Disallow**: Requests `requestDisallowInterceptTouchEvent` to prevent parent scroll views from stealing the drag.

## Java-to-C++ Translation Guide
*   **Event Injection**: This requires the UI framework to support injecting events into a specific view that might be in a different window/layer.

## Implementation Risks
*   **Coordinate mapping**: Accurately mapping global/screen coordinates between two detached views.
