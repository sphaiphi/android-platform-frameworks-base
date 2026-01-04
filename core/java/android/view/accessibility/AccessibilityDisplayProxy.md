# AccessibilityDisplayProxy - Reverse Engineering Documentation

## Executive Summary
A System API that allows a privileged app (with `MANAGE_ACCESSIBILITY`) to act as a proxy for accessibility interactions on a specific display. This is likely used for features like Companion Device Manager or virtual displays where a separate app handles accessibility for that display.

## Architecture
*   **Proxy Pattern**: Acts as an intermediary. It implements `IAccessibilityServiceClient` via an inner class `IAccessibilityServiceClientImpl` to receive callbacks from the system.
*   **Connection**: Manages a connection ID (`mConnectionId`) established via `AccessibilityInteractionClient`.

## Key Methods
*   **`getWindows`**: Queries windows for the proxied display using `AccessibilityInteractionClient`.
*   **`findFocus`**: Finds the focused node on the display.
*   **`setInstalledAndEnabledServices`**: Tells the system which accessibility services are interested in this display (distinct from phone-level services).

## Java-to-C++ Translation Guide
*   **Executor**: Uses `Executor` for callbacks. C++ could use a `TaskRunner` or `Looper`.
*   **Binder**: Wraps `IAccessibilityServiceClient`.
