# InputWindowHandle - Reverse Engineering Documentation

## Executive Summary
`InputWindowHandle` is a descriptor object used by the system to configure how a window receives input. It contains geometry (frame), touchable regions, and various flags (`InputConfig`) that control focusability, touchability, and security properties like touch occlusion.

## Architecture Overview
*   **Role**: Input configuration descriptor.
*   **JNI Centric**: Wraps a native C++ `InputWindowHandle`.
*   **Lifecycle**: Managed via `nativeDispose()` in the finalizer.

## Data Model

### 1. Geometry and Layout
*   **`frame`**: `Rect` - The window's bounds in screen coordinates.
*   **`touchableRegion`**: `Region` - The exact area within the frame where touches are accepted.
*   **`transform`**: `Matrix` - Mapping from screen-space to window-space coordinates.

### 2. Configuration Flags (`InputConfig`)
*   `NOT_FOCUSABLE`, `NOT_TOUCHABLE`: Basic interaction control.
*   `WATCH_OUTSIDE_TOUCH`: Receives `ACTION_OUTSIDE` if a touch happens outside the window.
*   `SPY`: Allows monitoring input without consuming it.
*   `SENSITIVE_FOR_PRIVACY`: Marks the window as containing sensitive content.

### 3. Security
*   **`touchOcclusionMode`**: Controls how touches are handled when the window is obscured by another layer (e.g., `BLOCK_UNTRUSTED`).

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Wrap `android::InputWindowHandle`.
*   **Region Handling**: Use `android::Region` for the `touchableRegion`.

## Implementation Risks
*   **Coordinate Sync**: The `transform` matrix and `frame` must be kept perfectly in sync with the `SurfaceControl`'s geometry to ensure accurate touch dispatch.
*   **Memory Pressure**: `InputWindowHandle` objects are frequently updated during layout; ensure the native handle pooling is efficient.
