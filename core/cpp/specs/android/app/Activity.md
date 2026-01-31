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
*   **Namespace**: `android::app`
*   **Complexity**: This is one of the most complex classes.
*   **Windowing**: Needs tight integration with the C++ windowing system (e.g., Wayland/SurfaceFlinger client).
*   **Lifecycle**: The state machine must be replicated exactly.
*   **Context**: Inherits all Context capabilities via `ContextThemeWrapper`.

## C++ Implementation Specification

### 1. Type Definitions & Enums
```cpp
namespace android::app {

enum class ActivityState {
    INITIALIZED,
    CREATED,
    STARTED,
    RESUMED,
    PAUSED,
    STOPPED,
    DESTROYED
};

} // namespace android::app
```

### 2. Class Definition (High-Level)
```cpp
namespace android::app {

class Activity : public android::view::ContextThemeWrapper {
public:
    Activity() = default;
    virtual ~Activity() = default;

    // Lifecycle Callbacks (Protected to match Java)
protected:
    virtual void on_create(const android::os::Bundle& saved_instance_state);
    virtual void on_start();
    virtual void on_resume();
    virtual void on_pause();
    virtual void on_stop();
    virtual void on_destroy();
    virtual void on_save_instance_state(android::os::Bundle& out_state);

public:
    // API
    auto set_content_view(int layout_res_id) -> void;
    auto finish() -> void;
    auto get_state() const noexcept -> ActivityState;

    // Internal State Management (Called by ActivityThread)
    auto perform_create(const android::os::Bundle& icicle) -> void;
    auto perform_start() -> void;
    auto perform_resume() -> void;
    auto perform_pause() -> void;
    auto perform_stop() -> void;
    auto perform_destroy() -> void;

private:
    ActivityState m_state{ActivityState::INITIALIZED};
    // m_window, m_window_manager, etc. (to be implemented in later tracks)
};

} // namespace android::app
```

### 3. Lifecycle State Machine
*   **`perform_create`**: Sets state to `CREATED`, calls `on_create`.
*   **`perform_start`**: Sets state to `STARTED`, calls `on_start`.
*   **`perform_resume`**: Sets state to `RESUMED`, calls `on_resume`.
*   **`perform_pause`**: Sets state to `PAUSED`, calls `on_pause`.
*   **`perform_stop`**: Sets state to `STOPPED`, calls `on_stop`.
*   **`perform_destroy`**: Sets state to `DESTROYED`, calls `on_destroy`.

### 4. Context Integration
*   `Activity` inherits from `ContextThemeWrapper`.
*   The `mBase` context (set via `attachBaseContext`) should be a `ContextImpl` instance.

## Implementation Risks
*   **Thread Safety**: Must run on the main UI thread.
*   **Memory Leaks**: Context leaks are common if not handled correctly (Activity Context vs Application Context).
