# WindowManager - Reverse Engineering Documentation

## Executive Summary
`WindowManager` is the primary interface used by applications to interact with the system's window manager (WMS). It allows apps to add, update, and remove windows on a specific display. It is also responsible for managing `WindowMetrics` and coordinate systems for touch events.

## Architecture Overview
*   **Interface**: Extends `ViewManager`.
*   **Implementation**: `WindowManagerImpl` (client-side) which delegates to `WindowManagerGlobal`.
*   **IPC**: Communicates with the `WindowManagerService` (WMS) in the system server via `IWindowManager` and `IWindowSession`.
*   **Key Inner Class**: `LayoutParams` - Metadata describing how a window should be laid out, its type, flags, and format.

## Detailed Functionality

### 1. Window Management
*   **`addView(View, ViewGroup.LayoutParams)`**: Registers a new window with WMS. This creates a `ViewRootImpl` internally.
*   **`updateViewLayout()`**: Modifies an existing window's attributes (e.g., resizing or changing flags).
*   **`removeView()` / `removeViewImmediate()`**: Unregisters the window.

### 2. LayoutParams (The Protocol)
*   **`type`**: Determines the window's role (APPLICATION, SUB_WINDOW, SYSTEM_ALERT).
*   **`flags`**: Controls interaction (NOT_FOCUSABLE, TOUCHABLE, SCALED).
*   **`softInputMode`**: Determines how the window reacts to the software keyboard.

### 3. Display & Metrics
*   **`getDefaultDisplay()`**: Returns the `Display` this manager is associated with.
*   **`getCurrentWindowMetrics()`**: Provides the size and insets of the window in its current state (useful for multi-window).

### 4. Special Operations
*   **Screenshots**: APIs for triggering system-level screenshots.
*   **Transitions**: Support for Activity and Window transitions.

## Java-to-C++ Translation Guide
*   **Service Binding**: Use `ServiceManager` to obtain `sp<IWindowManager>`.
*   **Data Structures**: `LayoutParams` must be manually marshalled to a Parcel if not using AIDL-generated code.
*   **Lifecycle**: The client-side `WindowManager` must track all active `ViewRootImpl` (or native root) instances to ensure clean disposal.

## Implementation Risks
*   **Token Security**: Windows require a valid `IBinder` token (usually from an `Activity`) to be added. Adding windows with null or invalid tokens throws `BadTokenException`.
*   **Resource Leakage**: Failing to `removeView` when an activity is destroyed leads to window leaks in WMS.
*   **Race Conditions**: Layout updates and input event dispatching are asynchronous; synchronization with `ViewRootImpl` is handled via `IWindowSession`.