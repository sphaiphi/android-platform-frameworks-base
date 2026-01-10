# AccessibilityManager - Reverse Engineering Documentation

## Executive Summary
The central system service manager for Accessibility. It bridges the app context with the `AccessibilityManagerService` (system_server). It handles enabling/disabling accessibility, sending events, and querying service state.

## Architecture
*   **Service Wrapper**: Holds `IAccessibilityManager` binder interface.
*   **Client Interface**: Implements `IAccessibilityManagerClient` to receive state updates from system_server.
*   **Listeners**: Manages lists of listeners for state changes (accessibility enabled, touch exploration, high contrast text, etc.).

## Key Methods
*   **`sendAccessibilityEvent`**: Checks if accessibility is enabled, then calls service to dispatch event.
*   **`getRecommendedTimeoutMillis`**: Logic to determine UI timeout based on user preferences and content type (icons vs controls).
*   **`addAccessibilityStateChangeListener`**: Registers local listeners.

## Java-to-C++ Translation Guide
*   **Binder**: Client/Server model.
*   **Observer Pattern**: Manages local callbacks.
