# GameSession - Reverse Engineering Documentation

## Executive Summary
`GameSession` represents an active interaction with a specific game task. It provides a facility for the game service to render an overlay on top of the game and handle user interactions, screenshots, and game restarts.

## Architecture Overview
*   **Overlay Mechanism**: Uses `SurfaceControlViewHost` to render a view hierarchy from the service process into the game's window space.
*   **Lifecycle**:
    *   `onCreate()`: Session initialized.
    *   `onGameTaskFocusChanged(boolean)`: Called when the game task gains or loses focus.
    *   `onDestroy()`: Session ending.
*   **State Machine**: Manages transitions between `INITIALIZED`, `CREATED`, `TASK_FOCUSED`, `TASK_UNFOCUSED`, and `DESTROYED`.

## Detailed Functionality

### UI Management
*   **`setTaskOverlayView(View, LayoutParams)`**: Sets the content of the game overlay. The root view (`GameSessionRootView`) automatically resizes to match the game window.
*   **`onTransientSystemBarVisibilityFromRevealGestureChanged(boolean)`**: Notifies the session when system bars (status/nav) become visible due to gestures, allowing the overlay to adjust its UI.

### Game Control
*   **`restartGame()`**: Forces the game to relaunch.
*   **`takeScreenshot(Executor, ScreenshotCallback)`**: Captures a screenshot of the game task.
*   **`startActivityFromGameSessionForResult(...)`**: Launches a provider Activity within the same activity stack, providing a way to show complex UI (like settings) that returns a result.

### IPC
*   **`IGameSession.Stub`**: Internal implementation to receive lifecycle events from the system server.
*   **`IGameSessionController`**: Provided during `attach()`, used to perform actions like restarting the game or taking screenshots.

## API Reference

### Inner Classes
*   `ScreenshotCallback`: Callback for screenshot results.
*   `LifecycleState`: Enum for internal state tracking.

## Java-to-C++ Translation Guide

### View Hosting
*   **Java**: `SurfaceControlViewHost`.
*   **C++**: Requires `ASurfaceControl` and `Surface` NDK APIs. The overlay rendering logic is the most complex part to translate.

### Threading
*   **Java**: Lifecycle methods are called on the main thread via `Handler`.
*   **C++**: Must ensure that UI updates and state transitions happen on a consistent thread (e.g., a dedicated UI thread).

## Implementation Risks
*   **Security**: Overlay views must be trusted as they can intercept touches intended for the game.
*   **Performance**: Rendering a complex overlay on top of a heavy game requires efficient GPU usage and minimal overhead.
*   **Resizing**: Must handle configuration changes (rotation, window resizing) smoothly by relayouting the `SurfaceControlViewHost`.
