# ImeInsetsSourceConsumer - Reverse Engineering Documentation

## Executive Summary
`ImeInsetsSourceConsumer` is a specialized `InsetsSourceConsumer` that manages the visibility, animation, and lifecycle of the Soft Keyboard (IME) insets. It handles the complex coordination between the application's window, the IME's window, and the system's `InputMethodManager`.

## Architecture Overview
*   **Role**: Keyboard inset lifecycle manager.
*   **Hierarchy**: Inherits from `InsetsSourceConsumer`.
*   **Key Dependencies**:
    *   `InsetsController`: For driving animations.
    *   `InputMethodManager`: For requesting the IME to show or hide.

## Detailed Functionality

### 1. Visibility Control
*   **`requestShow()`**: Sends a request to the system to display the keyboard. It tracks whether the request is "delayed" (waiting for focus or control).
*   **`requestHide()`**: Notifies the system that the keyboard should be dismissed.

### 2. Animation Integration
*   **`onAnimationStateChanged()`**: Syncs the visual animation of the keyboard with its internal visibility state. Handles the "Post-commit" phase of predictive back gestures.

### 3. Surface Management
*   **`removeSurface()`**: Triggers the removal of the IME's rendering surface via `InputMethodManager`.

## Java-to-C++ Translation Guide
*   **Native Link**: Links to the `ID_IME` source in the native `InsetsState`.
*   **IPC**: Extensive usage of `IInputMethodManager` (via Binder).

## Implementation Risks
*   **Focus Lag**: The consumer must wait for `hasLeash()` before starting an animation. Starting too early results in a jump cut.
*   **Perceptibility**: Correctly reporting whether the keyboard is "perceptible" (visible to the user) is vital for system-wide statistics and power management.
