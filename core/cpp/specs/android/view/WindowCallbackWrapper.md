# WindowCallbackWrapper - Reverse Engineering Documentation

## Executive Summary
`WindowCallbackWrapper` is a simple decorator (proxy) for the `Window.Callback` interface. it passes all calls through to a wrapped instance, allowing subclasses to intercept only specific methods (like `dispatchKeyEvent`) while maintaining the default behavior for everything else.

## Architecture Overview
*   **Role**: Window event proxy.
*   **Pattern**: Decorator Pattern.

## Detailed Functionality
*   Proxies all standard window callbacks:
    *   Input events (`dispatchKeyEvent`, `dispatchTouchEvent`, etc.)
    *   Menu events (`onCreatePanelView`, `onMenuItemSelected`)
    *   Window lifecycle (`onAttachedToWindow`, `onWindowFocusChanged`)
    *   Search and Action Modes.

## Java-to-C++ Translation Guide
*   **Pattern**: In C++, implement as a class that stores a `sp<Window::Callback>` and delegates virtual calls.

## Implementation Risks
*   **Null Checks**: The wrapper strictly requires a non-null instance to wrap.
