# ToastPresenter - Reverse Engineering Documentation

## Executive Summary
`ToastPresenter` is a helper class responsible for the low-level UI operations of displaying a toast message. It handles layout inflation, `WindowManager` interactions (adding/removing views), accessibility event dispatching, and synchronization with the `NotificationManagerService`. It encapsulates the logic for both standard text toasts and custom toast views.

## Architecture Overview
- **Role**: Presenter / UI Controller.
- **Context**: Runs either in the application's process (for app-rendered toasts) or in the SystemUI process (for system-rendered toasts).
- **Key Dependencies**:
    - `WindowManager`: For adding the toast as a top-level window.
    - `IAccessibilityManager`: For notifying accessibility services about the toast.
    - `INotificationManager`: For signaling completion of the toast display.
- **Window Management**: Uses `WindowManager.LayoutParams.TYPE_TOAST` and special flags to ensure the toast is non-interactive and transient.

## Detailed Functionality

### View Generation (`getTextToastView`)
**Purpose**: Creates the default view for a text-based toast.
**Algorithm**:
1.  Inflates `R.layout.transient_notification` (or `_with_icon`).
2.  Locates the `TextView` with ID `com.android.internal.R.id.message`.
3.  Sets the provided `CharSequence` text.

### Layout Parameter Configuration (`createLayoutParams`)
**Purpose**: Initializes the `WindowManager.LayoutParams` specific to toast windows.
**Algorithm**:
1.  Sets width/height to `WRAP_CONTENT`.
2.  Sets format to `TRANSLUCENT` and animations to `R.style.Animation_Toast`.
3.  Sets window type to `TYPE_TOAST`.
4.  Applies flags:
    - `FLAG_KEEP_SCREEN_ON`: Prevents screen dimming while toast is visible.
    - `FLAG_NOT_FOCUSABLE`: Toast cannot receive input focus.
    - `FLAG_NOT_TOUCHABLE`: Toast does not intercept touch events (pass-through).
5.  Calls `setShowForAllUsersIfApplicable` to handle cross-user package visibility.

### Showing the Toast (`show`)
**Purpose**: Displays the toast view on the screen.
**Algorithm**:
1.  **State Check**: Ensures no other toast is currently showing via this presenter.
2.  **Layout Adjustment**: Calls `adjustLayoutParams` to set the gravity, offsets, margins, and the `windowToken` provided by the system.
3.  **Timeout Calculation**: Sets `params.hideTimeoutMilliseconds` (4s for SHORT, 7s for LONG) to ensure the system cleans up if the app crashes.
4.  **View Insertion**: Calls `WindowManager.addView(view, params)`.
5.  **Side Effects**:
    - Dispatches an accessibility event (`TYPE_NOTIFICATION_STATE_CHANGED`).
    - Executes the `onToastShown()` callback.

### Hiding the Toast (`hide`)
**Purpose**: Removes the toast view and cleans up.
**Algorithm**:
1.  **View Removal**: Calls `WindowManager.removeViewImmediate(mView)`.
2.  **Notification Cleanup**: Calls `mNotificationManager.finishToken(mPackageName, mToken)` to tell the system service the window is gone.
3.  **Callback**: Executes `onToastHidden()`.
4.  **State Reset**: Nullifies `mView` and `mToken`.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `SHORT_DURATION_TIMEOUT` | `long` | 4000ms. Hard timeout for short toasts. |
| `LONG_DURATION_TIMEOUT` | `long` | 7000ms. Hard timeout for long toasts. |
| `mParams` | `WindowManager.LayoutParams` | Reusable layout parameters for the toast window. |
| `mView` | `View` | The view currently being displayed. |
| `mToken` | `IBinder` | The binder token identifying the toast instance in the system. |

## API Reference
- `show(View, IBinder, IBinder, int, int, int, int, float, float, ITransientNotificationCallback)`: Detailed show method with all geometry parameters.
- `hide(ITransientNotificationCallback)`: Removes the current toast.
- `updateLayoutParams(...)`: Adjusts position/margins of an *already showing* toast (e.g., on rotation).
- `getTextToastView(Context, CharSequence)`: Static helper for standard UI.

## Java-to-C++ Translation Guide

### Window Management
- **Native Windowing**: The C++ implementation must interact with the native `WindowManager` (e.g., via `ISurfaceComposer` or a C++ wrapper for `WindowManager`).
- **Layout Params**: Translate `WindowManager.LayoutParams` fields to the native equivalent. Pay special attention to `privateFlags` and the logic in `setShowForAllUsersIfApplicable`.

### Layout Inflation
- **Resources**: In C++, UI layout should ideally be defined in code or loaded via a C++-compatible layout engine, as `LayoutInflater` is Java-specific.

### Accessibility
- **IAccessibilityManager**: Use `android::interface_cast<IAccessibilityManager>(...)`.
- **Event Dispatch**: The `trySendAccessibilityEvent` logic is quite specific (explicitly avoids singleton `AccessibilityManager` to handle multi-user). This pattern must be followed in C++ to avoid leaking or misrouting events in multi-user environments.

### Synchronization
- **Error Handling**: `show` catches `BadTokenException` and `InvalidDisplayException`. These represent race conditions where the display was removed or the token was revoked by the system between the `enqueue` and `show` calls. The C++ implementation must handle these native errors gracefully.

## Implementation Risks
- **Race Conditions**: There is an inherent race between the system service revoking a token and the app trying to add a window. The `addView` call must be inside a try-catch or error-check block.
- **Accessibility Leaks**: The comment in `trySendAccessibilityEvent` warns about a leak when registering clients with `IAccessibilityManager`. The `removeClient()` call is mandatory.
- **Multi-User**: `ToastPresenter` is designed to be multi-user aware by using `context.getUserId()` and checking `config_toastCrossUserPackages`.
- **Z-Order**: Toasts must stay on top. In C++, ensure the window type (`TYPE_TOAST`) is mapped to a layer that is above most app content but below system overlays.
