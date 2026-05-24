# ImeFocusController - Reverse Engineering Documentation

## Executive Summary
`ImeFocusController` is responsible for managing the input method focus within a `ViewRootImpl`. it determines when a window is eligible to use an IME and coordinates focus transitions between views to ensure the keyboard is correctly shown or hidden.

## Architecture Overview
*   **Role**: Window-local IME focus manager.
*   **Delegate**: Proxies core operations to an `InputMethodManagerDelegate`.
*   **Threading**: Annotated with `@UiThread`, as focus changes are tied to the View hierarchy.

## Detailed Functionality

### 1. Window Focus Transitions
*   **`onTraversal()`**: Re-evaluates focus during the layout pass.
*   **`onPreWindowFocus()`** / **`onPostWindowFocus()`**: Notifies the IME system when the window gains or loses global focus.

### 2. View Focus Tracking
*   **`onViewFocusChanged()`**: Triggered when focus moves between widgets (e.g., from one `EditText` to another).
*   **`onScheduledCheckFocus()`**: Performs a lazy check to ensure the IME is targeting the correct view.

### 3. Input Processing
*   **`onProcessImeInputStage()`**: Intercepts input events (like the Back key) to decide if they should be sent to the IME before the application.

## Java-to-C++ Translation Guide
*   **Pattern**: Delegate Pattern.
*   **State**: Tracks a boolean `mHasImeFocus` which should be synchronized with the native window flags.

## Implementation Risks
*   **Race Conditions**: Mismatched notifications between `View` focus and `Window` focus can lead to "keyboard flickers" or focus getting stuck.
*   **Display Changes**: Moving a `ViewRootImpl` to a new display requires refreshing the IME delegate to target the correct `InputMethodManager` instance.
