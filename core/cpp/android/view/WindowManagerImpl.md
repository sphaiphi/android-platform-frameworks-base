# WindowManagerImpl - Reverse Engineering Documentation

## Executive Summary
`WindowManagerImpl` is the concrete implementation of the `WindowManager` interface. It is a lightweight wrapper that delegates most of its work to `WindowManagerGlobal`. Each `Context` (Activity, Service) gets its own `WindowManagerImpl` instance, which binds new windows to that specific context's `Display` and `Token`.

## Architecture Overview
*   **Role**: Context-aware window manager proxy.
*   **Context**: Holds a reference to the `Context` and the `ParentWindow` (if any).
*   **Delegation**: Calls `WindowManagerGlobal` for the heavy lifting.

## Detailed Functionality
*   **`addView()`**: Adds the token (if missing) from the parent window or context before delegating to Global.
*   **`createLocalWindowManager()`**: Creates a new instance linked to a child window (used for Dialogs).

## Java-to-C++ Translation Guide
*   **Structure**: In C++, this can be a simple class holding a pointer to the global window manager and the context state.

## Implementation Risks
*   **Token Association**: Correctly propagating the Activity token is crucial for WMS to associate windows with the correct app lifecycle.
