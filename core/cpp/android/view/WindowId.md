# WindowId - Reverse Engineering Documentation

## Executive Summary
`WindowId` is a safe, Parcelable identifier for a window that can be passed between processes. It provides a limited API for observing the focus state of a window without exposing the full `IWindow` interface, ensuring security while enabling cross-process interaction.

## Architecture Overview
*   **Role**: Secure cross-process window handle.
*   **Communication**: Wraps an `IWindowId` binder object.
*   **Observer Pattern**: Uses `FocusObserver` to notify clients about focus changes.

## Detailed Functionality
*   **`isFocused()`**: Queries the current focus state of the window.
*   **`registerFocusObserver()`**: Subscribes to focus updates. it manages a mapping of input tokens to `WindowId` instances to ensure correct callback routing.

## Java-to-C++ Translation Guide
*   **IPC**: Use the `IWindowId` AIDL interface.
*   **Observer**: Implement `BnWindowFocusObserver` for the native callback.

## Implementation Risks
*   **Reference Management**: `FocusObserver` uses a `HashMap` of registrations; ensure entries are removed when the observer or window is no longer needed.
