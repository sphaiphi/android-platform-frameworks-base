# Activity - Reverse Engineering Documentation

## Executive Summary
`Activity` is the core component for user interaction in Android. It represents a single screen with a user interface. It manages a `Window` (typically `PhoneWindow`), handles input events, and follows a complex lifecycle managed by the system (`ActivityTaskManager`).

## Architecture Overview
*   **Inheritance**: `ContextThemeWrapper` -> `ContextWrapper` -> `Context`.
*   **Interfaces**: `LayoutInflater.Factory2`, `Window.Callback`, `KeyEvent.Callback`, `OnCreateContextMenuListener`, `ComponentCallbacks2`.
*   **Key Components**:
    *   `mWindow`: The `Window` object (PhoneWindow).
    *   `mWindowManager`: Interface to the window manager.
    *   `mMainThread`: Reference to `ActivityThread`.
    *   `mInstrumentation`: System instrumentation for testing/monitoring.
    *   `mFragments`: `FragmentController` (manages Fragments).
    *   `mUiThread`: The thread the activity runs on.

## Detailed Functionality

### Lifecycle
*   **Core Loop**: `onCreate` -> `onStart` -> `onResume` -> `onPause` -> `onStop` -> `onDestroy`.
*   **State Restoration**: `onSaveInstanceState`, `onRestoreInstanceState`.
*   **Configuration**: `onConfigurationChanged`.

### UI Management
*   `setContentView`: Inflates layout resources into the Window.
*   `findViewById`: Delegates to `Window`.
*   `setVisible`: Controls visibility of the DecorView.

### Intent & Result
*   `startActivity`, `startActivityForResult`: Uses `mInstrumentation.execStartActivity` which calls into `ActivityTaskManagerService`.
*   `setResult`, `finish`: Closes the activity and passes data back.

### Fragment Management
*   **Manager**: Contains a `FragmentManagerImpl` via `FragmentController`.
*   **Transactions**: Supports committing transactions.

### Window Callbacks
*   `dispatchKeyEvent`, `dispatchTouchEvent`: Handled by `Window.Callback` methods to allow interception before View hierarchy.

## Java-to-C++ Translation Guide
*   **Complexity**: This is one of the most complex classes.
*   **Windowing**: Needs tight integration with the C++ windowing system (e.g., Wayland/SurfaceFlinger client).
*   **Lifecycle**: The state machine must be replicated exactly.
*   **Context**: Inherits all Context capabilities.

## Implementation Risks
*   **Thread Safety**: Must run on the main UI thread.
*   **Memory Leaks**: Context leaks are common if not handled correctly (Activity Context vs Application Context).
