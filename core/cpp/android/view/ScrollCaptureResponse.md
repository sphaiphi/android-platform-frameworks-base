# ScrollCaptureResponse - Reverse Engineering Documentation

## Executive Summary
`ScrollCaptureResponse` is a Parcelable data class that contains the result of a scroll capture discovery request. It indicates whether a scrollable target was found and, if successful, provides the active connection and metadata about the window and its scrollable bounds.

## Data Model
*   **`mConnection`**: `IScrollCaptureConnection` - The handle used to control the capture.
*   **`mWindowBounds`**: `Rect` - The physical location of the window.
*   **`mBoundsInWindow`**: `Rect` - The area within the window that can be scrolled.
*   **`mDescription`**: `String` - Human-readable status (for debugging).
*   **`mMessages`**: `List<String>` - Detailed log of why a target was or wasn't selected.

## Detailed Functionality
*   **`isConnected()`**: Checks if a valid, alive binder connection is present.
*   **`close()`**: Helper to shut down the connection if it's no longer needed.

## Java-to-C++ Translation Guide
*   **Structure**: Map to a C++ `class ScrollCaptureResponse`.
*   **Parcelling**: Marshalling must match the `DataClass` generated order.

## Implementation Risks
*   **Binder Lifecycle**: The `mConnection` object must be managed carefully to ensure it's not closed prematurely while the screenshot tool is still active.
