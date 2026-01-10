# Window - Reverse Engineering Documentation

## Executive Summary
`Window` is an abstract base class for a top-level window look and behavior policy. It manages the standard UI components of a window (background, title, panels, menus) and provides a callback mechanism for the system to communicate with the window owner (usually an `Activity`). The standard implementation is `PhoneWindow`.

## Architecture Overview
*   **Role**: Policy manager for UI features.
*   **Key Component**: `DecorView` - The root view of the window's view hierarchy.
*   **Context**: Associated with a `Context` (usually an `Activity`).
*   **Features**: Manages window features like `FEATURE_NO_TITLE`, `FEATURE_ACTION_BAR`, and transitions.

## Detailed Functionality

### 1. Feature Management
*   **`requestFeature(int)`**: Enables specific window behaviors (e.g., Overlay Action Bar).
*   **`setContentView(int/View)`**: Sets the main content area of the window (inside the `DecorView`).

### 2. Window Callbacks
*   **`Window.Callback`**: The interface that `Activity` implements to receive events:
    *   `dispatchKeyEvent`, `dispatchTouchEvent`: Intercept events before the View tree.
    *   `onAttachedToWindow`, `onDetachedFromWindow`.
    *   `onContentChanged`: Called when `setContentView` is invoked.

### 3. Visual Attributes
*   **Layout Params**: Manages `WindowManager.LayoutParams` (flags like `FLAG_FULLSCREEN`, `FLAG_KEEP_SCREEN_ON`).
*   **Colors**: `setStatusBarColor()`, `setNavigationBarColor()`.
*   **Dimming**: `setDimAmount()`.

### 4. Background & Decor
*   The `DecorView` is created by the `Window` implementation. It provides the "frame" for the app content, including the status bar and navigation bar backgrounds.

## Java-to-C++ Translation Guide
*   **Policy Pattern**: In C++, this can be implemented as a bridge between the display server client and the application's UI components.
*   **Callback Interface**: Use a virtual base class for `Window::Callback`.
*   **Window Types**: Mapping `WindowManager.LayoutParams.type` to C++ windowing layer types.

## Implementation Risks
*   **State Leakage**: Window features and flags must be set before the window is added to the `WindowManager`.
*   **Z-Order Management**: Child windows (panels, sub-panels) require careful token and parent-window management.