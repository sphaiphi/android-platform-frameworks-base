# SoftInputWindow - Reverse Engineering Documentation

## Executive Summary
`SoftInputWindow` is the specific `Dialog` implementation used by `InputMethodService` to host the IME UI. It handles proper window token association and state management (shown, rejected, destroyed).

## Architecture Overview
*   **Inheritance**: `Dialog` -> `SoftInputWindow`.

## Detailed Functionality

### Token Management (`setToken`)
*   **State Machine**: `TOKEN_PENDING` -> `TOKEN_SET`.
*   Sets `WindowManager.LayoutParams.token` to the InputMethod token.
*   Calls `show()` immediately (invisible) to attach the window to WindowManager.

### Show/Dismiss
*   **`show()`**: Handles states `SHOWN_AT_LEAST_ONCE` vs `REJECTED_AT_LEAST_ONCE` (BadTokenException handling).
*   **`dismissForDestroyIfNecessary`**: Disables exit animations to prevent race conditions during IME switching.

### Dispatcher
*   Holds `KeyEvent.DispatcherState` and resets it on window focus change.

## Data Model
*   `mWindowState`: State enum.
*   `mToken`: Binder token.

## Java-to-C++ Translation Guide
*   **Windowing**: Mapping `Dialog` behavior to native window creation. The key is setting the correct Window Type (`TYPE_INPUT_METHOD`) and Token.

## Implementation Risks
*   **BadTokenException**: A common crash in Android if the token is invalid/expired. The state machine and try-catch blocks in `show()` are critical for stability.
