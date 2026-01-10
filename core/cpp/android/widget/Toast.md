# Toast - Reverse Engineering Documentation

## Executive Summary
`Toast` is a component used to display transient, non-interactive messages to the user. It manages the lifecycle of these messages by communicating with the system's `NotificationManagerService`. Modern Android versions (Android 11+) distinguish between "Custom Toasts" (app-rendered views) and "Text Toasts" (system-rendered), with significant restrictions and deprecations applied to custom toasts to prevent UI abuse and ensure consistent behavior across the platform.

## Architecture Overview
- **Core Component**: `Toast` class.
- **IPC Mechanism**: Uses `INotificationManager` (AIDL) to enqueue and cancel toasts.
- **Inner Interface**: `TN` (Transient Notification), a Binder stub (`ITransientNotification.Stub`) that the system service calls back into to show/hide the toast view.
- **Presenter**: Delegates actual window management and view rendering to `ToastPresenter`.
- **System Change**: `CHANGE_TEXT_TOASTS_IN_THE_SYSTEM` (Android 12+) forces text-only toasts to be rendered by SystemUI rather than the application process.

## Detailed Functionality

### Toast Creation (`makeText`)
**Purpose**: Static factory methods to create standard text toasts.
**Algorithm**:
1.  Instantiates a new `Toast` with a `Looper`.
2.  If `CHANGE_TEXT_TOASTS_IN_THE_SYSTEM` is enabled:
    - Stores the text in `mText`.
3.  Else (Legacy):
    - Generates a standard view using `ToastPresenter.getTextToastView(context, text)` and stores it in `mNextView`.
4.  Sets the duration.

### Showing a Toast (`show`)
**Purpose**: Enqueues the toast for display.
**Algorithm**:
1.  Validates that either a view or text is set.
2.  Retrieves the `INotificationManager` service.
3.  **Text Toast Path** (Modern):
    - Calls `service.enqueueTextToast` passing the text, duration, and a `CallbackBinder`.
4.  **Custom Toast Path** (or Legacy Text):
    - Sets `mNextView` (or a weak reference to it) into the `TN` object.
    - Calls `service.enqueueToast` passing the `TN` binder.
5.  The system service manages a queue and calls back into `TN.show()` when it's this toast's turn.

### The `TN` Inner Class (Callback Handler)
**Purpose**: Handles the "Show", "Hide", and "Cancel" messages from the system service on the app's UI thread.
**Algorithm**:
1.  `show(IBinder windowToken)`: Receives a window token from the system and posts a `SHOW` message to the handler.
2.  `handleShow(windowToken)`:
    - Checks if a cancel is pending.
    - Uses `ToastPresenter.show()` to add the view to the window manager.
    - Passes offsets, gravity, and margins.
3.  `handleHide()`: Uses `ToastPresenter.hide()` to remove the view from the window manager.

### Property Management
- **Duration**: `LENGTH_SHORT` (usually 2s) or `LENGTH_LONG` (usually 3.5s).
- **Gravity/Offsets**: Customizes where the toast appears. Note: These are ignored for system-rendered text toasts in newer Android versions.
- **Callbacks**: Allows apps to listen for `onToastShown` and `onToastHidden`.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mToken` | `Binder` | Unique identifier for this toast instance. |
| `mTN` | `TN` | Binder stub for system-to-app communication. |
| `mDuration` | `int` | `LENGTH_SHORT` or `LENGTH_LONG`. |
| `mNextView` | `View` | The custom view to show (if any). |
| `mText` | `CharSequence` | The text to show (for system-rendered toasts). |
| `mCallbacks` | `List<Callback>` | User-provided listeners for lifecycle events. |

## API Reference
- `show()`: Enqueues the toast.
- `cancel()`: Immediately removes the toast or prevents it from showing.
- `setText(CharSequence)`: Updates the message (only for toasts created via `makeText`).
- `setView(View)`: Sets a custom view (Deprecated).
- `setGravity(int, int, int)`: Sets position.
- `addCallback(Callback)`: Registers a listener.

## Java-to-C++ Translation Guide

### IPC and Service Discovery
- **ServiceManager**: Use `android::defaultServiceManager()` and `android::interface_cast<INotificationManager>(...)`.
- **Binder Stubs**: The `TN` class must be implemented as a C++ `BnTransientNotification` (generated from `ITransientNotification.aidl`).

### Threading and Looper
- **Handler/Looper**: Replace with `android::Looper` and a custom `android::MessageHandler` or `android::Handler` implementation.
- **Weak References**: Use `android::wp<T>` for child view references to avoid cycles, mirroring `WeakReference<View>`.

### UI Rendering
- **ToastPresenter**: A corresponding C++ `ToastPresenter` must be created to handle interaction with the native `WindowManager`.
- **View System**: Since `Toast` uses `android.view.View`, the C++ implementation assumes a native View framework is present.

### Compatibility Checks
- **Compatibility.isChangeEnabled**: The C++ implementation should query the `platform_compat` service if feature-flag parity is required.

## Implementation Risks
- **Window Tokens**: The security model relies on the system service providing a valid `windowToken` to the app. In C++, ensuring this token is handled correctly during `WindowManager::addView` is critical.
- **Memory Leaks**: `TN` is a Binder object. If not managed carefully (especially with the `mCallbacks` list), it can lead to process-level leaks.
- **Rate Limiting**: Background toasts are rate-limited by the system service. The C++ client shouldn't implement this logic but must handle the `RemoteException` or error codes if enqueuing fails.
- **Custom View Security**: Custom views are rendered in the app's process. Ensure that the `ToastPresenter` (C++) correctly handles window types (e.g., `TYPE_TOAST`) and flags (e.g., `FLAG_NOT_FOCUSABLE`).
