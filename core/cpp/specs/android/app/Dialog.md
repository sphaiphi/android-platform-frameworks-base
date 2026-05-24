# Dialog - Reverse Engineering Documentation

## Executive Summary
`Dialog` is the base class for floating windows. It manages a `Window` object, handles key events (Back, Menu), and provides lifecycle callbacks (`onStart`, `onStop`, `dismiss`). It acts as a controller for a Window that is distinct from the Activity's window.

## Architecture Overview
*   **Inheritance**: Implements `DialogInterface`, `Window.Callback`, `KeyEvent.Callback`.
*   **Composition**: Owns a `Window` (typically `PhoneWindow`) and a `WindowManager`.
*   **Lifecycle**: `create` -> `onStart` -> `show` -> `hide`/`dismiss` -> `onStop`.

## Detailed Functionality

### Window Management
*   Creates a `PhoneWindow` using the context's theme.
*   `setContentView`: Inflates layout into the window.
*   `show()`: Adds the window's decor view to the `WindowManager`.
*   `dismiss()`: Removes the decor view from the `WindowManager`.

### Event Handling
*   **Keys**: Handles BACK key to cancel/dismiss. Handles Search key.
*   **Touch**: Detects touches outside the window to cancel (if `canceledOnTouchOutside` is true).
*   **Menu**: Dispatches menu creation/selection to the Owner Activity (if set).

### Callbacks
*   `OnCancelListener`: When canceled (Back key).
*   `OnDismissListener`: When dismissed.
*   `OnShowListener`: When shown.

## API Reference
*   `show()`, `hide()`, `dismiss()`.
*   `setCancelable(boolean)`.
*   `setContentView(View)`.
*   `findViewById(int)`.

## Java-to-C++ Translation Guide
*   **Window System**: Requires a windowing abstraction (`Window`, `WindowManager`).
*   **Event Loop**: Must integrate with the input event dispatching loop.
*   **Handler**: Uses `Handler` for async message dispatching (dismiss/cancel messages).

## Implementation Risks
*   **Window Leaks**: Failing to remove the view from WindowManager on dismiss/destroy.
*   **Focus Management**: Dialogs steal focus; handling restoration on dismiss is handled by WM but needs verification.
