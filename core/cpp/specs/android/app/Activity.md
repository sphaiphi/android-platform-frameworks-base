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
*   **Internal Perform Methods**:
    *   `performCreate`: Initializes internal flags, calls `onCreate`.
    *   `performStart`: Executes pending fragment actions, calls `onStart` via `Instrumentation`.
    *   `performRestart`: Sets `mStopped = false`, calls `onRestart` via `Instrumentation`.
    *   `performResume`: Calls `onResume` via `Instrumentation`, calls `onPostResume`.
    *   `performPause`: Calls `onPause`, sets `mResumed = false`.
    *   `performStop`: Calls `onStop` via `Instrumentation`, sets `mStopped = true`.
    *   `performDestroy`: Calls `onDestroy`, sets `mDestroyed = true`, destroys the `Window`.

### UI Management
*   `setContentView`: Inflates layout resources into the Window.
*   `findViewById`: Delegates to `Window`.
*   `setVisible`: Controls visibility of the DecorView.

### Intent & Result
*   `startActivity`, `startActivityForResult`: Uses `mInstrumentation.execStartActivity` which calls into `ActivityTaskManagerService`.
*   `setResult`: Sets `mResultCode` and `mResultData` to be returned to the caller.
*   `finish`: Closes the activity and passes data back.
*   `dispatchActivityResult`: Dispatches a result received from `ActivityThread` to `onActivityResult` (or to fragments).

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
*   **Error Handling**: Use `std::expected<void, ActivityError>` for operations that can fail due to invalid state transitions or system errors.

## C++ Implementation Specification

### 1. Type Definitions & Enums
```cpp
namespace android::app {

enum class ActivityState {
    initialized,
    created,
    started,
    resumed,
    paused,
    stopped,
    destroyed
};

enum class ActivityError {
    invalid_state_transition,
    super_not_called,
    system_error
};

} // namespace android::app
```

### 2. Class Definition (Refined)
```cpp
namespace android::app {

class Activity : public android::view::ContextThemeWrapper {
public:
    Activity();
    explicit Activity(std::shared_ptr<android::content::Context> base);
    virtual ~Activity() = default;

    // Lifecycle Callbacks (Protected to match Java)
protected:
    virtual void on_create(const android::os::Bundle& saved_instance_state);
    virtual void on_start();
    virtual void on_restart();
    virtual void on_resume();
    virtual void on_pause();
    virtual void on_stop();
    virtual void on_destroy();
    virtual void on_save_instance_state(android::os::Bundle& out_state);
    virtual void on_activity_result(int32_t request_code, int32_t result_code, const std::optional<android::content::Intent>& data);

public:
    // API
    auto set_content_view(int layout_res_id) -> void;
    auto finish() -> void;
    auto get_state() const noexcept -> ActivityState;

    auto start_activity_for_result(const android::content::Intent& intent, int32_t request_code, std::optional<android::os::Bundle> options) -> void;
    auto set_result(int32_t result_code, std::optional<android::content::Intent> data) -> void;

    // System Hooks
    virtual void on_configuration_changed(const android::content::res::Configuration& new_config);
    virtual void on_low_memory();
    virtual void on_trim_memory(int32_t level);

    // Internal State Management (Called by ActivityThread)
    auto perform_create(const android::os::Bundle& icicle) -> std::expected<void, ActivityError>;
    auto perform_start() -> std::expected<void, ActivityError>;
    auto perform_restart() -> std::expected<void, ActivityError>;
    auto perform_resume() -> std::expected<void, ActivityError>;
    auto perform_pause() -> std::expected<void, ActivityError>;
    auto perform_stop() -> std::expected<void, ActivityError>;
    auto perform_destroy() -> std::expected<void, ActivityError>;

    auto dispatch_activity_result(const std::string& who, int32_t request_code, int32_t result_code, const android::content::Intent& data) -> void;

private:
    ActivityState m_state{ActivityState::initialized};
    bool m_called{false};
    bool m_resumed{false};
    bool m_stopped{false};
    bool m_destroyed{false};

    int32_t m_result_code{0}; // RESULT_CANCELED
    std::optional<android::content::Intent> m_result_data;

    // m_window, m_window_manager, etc.
};

} // namespace android::app
```

### 3. Lifecycle State Machine
*   **`perform_create`**: Sets state to `created`, calls `on_create`. Verifies `m_called`.
*   **`perform_start`**: Sets state to `started`, calls `on_start`. Verifies `m_called`.
*   **`perform_restart`**: Sets `m_stopped = false`, calls `on_restart`. Verifies `m_called`.
*   **`perform_resume`**: Sets state to `resumed`, calls `on_resume`. Verifies `m_called`. Sets `m_resumed = true`.
*   **`perform_pause`**: Calls `on_pause`. Verifies `m_called`. Sets `m_resumed = false`. Sets state to `paused`.
*   **`perform_stop`**: Calls `on_stop`. Verifies `m_called`. Sets `m_stopped = true`. Sets state to `stopped`.
*   **`perform_destroy`**: Sets `m_destroyed = true`, calls `on_destroy`. Sets state to `destroyed`.

### 4. Context Integration
*   `Activity` inherits from `ContextThemeWrapper`.
*   The `mBase` context (set via `attachBaseContext`) should be a `ContextImpl` instance.

## Implementation Risks
*   **Thread Safety**: Must run on the main UI thread.
*   **Memory Leaks**: Context leaks are common if not handled correctly.
*   **Super Call Check**: Java uses `mCalled` to ensure `super.onXXX()` is called. C++ must replicate this mechanism.