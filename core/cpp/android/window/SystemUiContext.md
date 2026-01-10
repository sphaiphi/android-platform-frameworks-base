# SystemUiContext - Reverse Engineering Documentation

## Executive Summary
`SystemUiContext` is a specialized `ContextWrapper` used by SystemUI components. It implements `ConfigurationDispatcher` to manage its own set of component callbacks and propagate configuration changes effectively, decoupling it from the standard Application context config loop.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` extends `ContextWrapper`
*   **Role**: Context specialization.

## Detailed Functionality

### `ConfigurationDispatcher`
*   **`dispatchConfigurationChanged`**: Delegates to `ComponentCallbacksController`.
*   **`shouldReportPrivateChanges`**: Returns `true`. This context cares about all changes (even private ones like theme assets updates).

### Callbacks
*   Overrides `register/unregisterComponentCallbacks` to use its local controller instead of the base context.

## Java-to-C++ Translation Guide
*   **Context**: C++ code typically doesn't have a direct `Context` equivalent. This class is relevant for UI-toolkit level C++ code or System Server internal resource management.

## Implementation Risks
*   **Flag**: Constructor checks `Flags.trackSystemUiContextBeforeWms()`.
