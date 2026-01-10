# InsetsController - Reverse Engineering Documentation

## Executive Summary
`InsetsController` is the central manager for all window insets (Status Bar, Navigation Bar, IME) within a window. It implements the `WindowInsetsController` interface, providing APIs to show, hide, and animate system bars. it coordinates between the server-provided controls and the application's view hierarchy.

## Architecture Overview
*   **Role**: System bar and IME manager.
*   **Key State**: Maintains an `InsetsState` describing the current system configuration.
*   **Lifecycle**: Tied to `ViewRootImpl`.

## Detailed Functionality

### 1. Visibility Control
*   **`show()` / `hide()`**: The primary entry points for apps to request system bar changes.
*   **`setRequestedVisibleTypes()`**: Tracks the intended state of each inset type.

### 2. Animation Management
*   **`controlWindowInsetsAnimation()`**: Allows apps to take direct frame-by-frame control of inset leashes.
*   **`applyAnimation()`**: Standard system-driven show/hide animations.

### 3. Consumer Mapping
*   **`InsetsSourceConsumer`**: For each inset type, the controller manages a consumer that handles the actual visibility logic and leash management.

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap `android::view::InsetsController`.
*   **IPC**: Proxies calls to `IWindowSession::updateRequestedVisibleTypes`.
*   **Animation**: Requires integration with a C++ animator (like Skia or a native ValueAnimator).

## Implementation Risks
*   **IME Sync**: Coordinating with the keyboard is extremely fragile. The controller must handle "Pending" requests when the keyboard is not yet ready or hasn't granted a leash.
*   **Z-Order**: The controller must ensure that animating system bars don't accidentally overlap or get clipped by the application's content incorrectly.
