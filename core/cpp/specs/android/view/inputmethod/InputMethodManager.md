# InputMethodManager - Reverse Engineering Documentation

## Executive Summary
The central client-side manager for interacting with the Input Method Framework. It coordinates between the App, the System Service (`InputMethodManagerService`), and the current IME.

## Architecture
*   **Singleton**: `getInstance()` (per display context).
*   **Service**: Talks to `IInputMethodManager`.
*   **Client**: Implements `IInputMethodClient`.
*   **InputConnection**: Manages the active `InputConnection` (`mServedInputConnection`) and the View being served (`mServedView`).

## Key Algorithms
*   **`showSoftInput`**: Requests IME visibility.
*   **`hideSoftInputFromWindow`**: Requests IME hide.
*   **`startInputInner`**: Initiates the handshake to start input on a view (Window focus gain).
*   **Focus Handling**: `DelegateImpl` handles window/view focus changes to auto-start input.

## Java-to-C++ Translation Guide
*   **Complexity**: Very complex logic involving Binder, ViewRootImpl, and async state management.
