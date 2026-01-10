# WindowContext - Reverse Engineering Documentation

## Executive Summary
`WindowContext` is a specialized `Context` implementation used for windows that aren't associated with an Activity (e.g., system overlays, software keyboards). It is "window-aware", meaning its `Resources` and `Configuration` are automatically adjusted based on the display area it occupies.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` extends `ContextWrapper` implements `WindowProvider`, `ConfigurationDispatcher`
*   **Role**: Non-activity UI Context.
*   **Key Components**:
    *   `WindowContextController`: Manages the lifecycle and attachment to WM.
    *   `WindowManager`: A specialized instance for this context.

## Detailed Functionality

### Lifecycle
*   **Creation**: `Context.createWindowContext(...)`.
*   **Attachment**: `attachToDisplayArea()` registers the context with the system server to start receiving config updates.
*   **Release**: `detachIfNeeded()` unregisters.

### Configuration Updates
*   Implements `ConfigurationDispatcher`.
*   `dispatchConfigurationChanged`: Notifies registered `ComponentCallbacks`.

### Reparenting
*   `reparentToDisplay(int displayId)`: Moves the context and its associated windows to a different display.

## Java-to-C++ Translation Guide
*   **Context Logic**: This class relies on `ContextImpl` and `ResourcesManager`. C++ translation is only relevant if implementing a native UI framework that needs to handle resource overrides per-window.

## Implementation Risks
*   **Leaking**: `finalize()` calls `release()`. Ensure C++ handles the token destruction correctly to avoid memory/binder leaks in the system server.
