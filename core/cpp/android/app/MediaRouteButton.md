# MediaRouteButton - Reverse Engineering Documentation

## Executive Summary
`MediaRouteButton` is a custom `View` that provides a standard UI entry point for media route selection. It displays a "Cast" icon that changes its visual state (e.g., animated while connecting, solid when connected) based on the status of media routes. Clicking the button launches a route chooser or controller dialog.

## Architecture Overview
- **Inheritance**: Extends `View`.
- **Core Components**:
    - `MediaRouter mRouter`: Used to query and monitor route states.
    - `MediaRouterCallback mCallback`: Internal listener for route-related events.
- **Visual States**:
    - `CHECKED_STATE_SET`: Used when connecting to a remote route.
    - `ACTIVATED_STATE_SET`: Used when connected to a remote route.
    - Supports `AnimationDrawable` for transitions.

## Detailed Functionality

### showDialogInternal()
**Purpose**: Displays the media route chooser or controller dialog.
**Mechanism**: Uses `MediaRouteDialogPresenter.showDialogFragment` to display a `DialogFragment` on the hosting activity.

### refreshRoute()
**Purpose**: Updates the button's icon and enabled state to match the system's current media route.
**Algorithm**:
1. Gets the currently selected route from `mRouter`.
2. Determines if the route is "remote" (not default) and if it is "connecting".
3. Updates `mRemoteActive` and `mIsConnecting` flags.
4. Calls `refreshDrawableState()` if states changed.
5. Enables/disables the view based on `mRouter.isRouteAvailable`.
6. Manages the starting/stopping of `AnimationDrawable` frames for smooth transitions.

### onDraw(Canvas canvas)
**Purpose**: Renders the "Cast" icon.
**Algorithm**: Calculates the centered bounds for `mRemoteIndicator` (the icon drawable) based on padding and view dimensions, then calls `mRemoteIndicator.draw(canvas)`.

### onAttachedToWindow() / onDetachedFromWindow()
**Purpose**: Manages `MediaRouter` callback registration to ensure discovery only happens when the view is active.

## API Reference
- `public void setRouteTypes(int types)`: Filters which routes trigger the button's visibility/interactivity.
- `public void showDialog()`: Programmatically opens the selection dialog.
- `public int getRouteTypes()`: Returns current filters.

## Java-to-C++ Translation Guide
- **Custom View Drawing**: Implement `onDraw` equivalents using a native rendering engine like Skia or a wrapper around `ASurfaceControl`.
- **Drawable State**: Map Java's state-list drawable logic to a C++ equivalent that handles state bitmasks (e.g., `android::ResTable`).
- **DialogFragment**: In a pure C++ environment, this would involve creating a native window or overlay using `WindowManager` or a similar UI abstraction.

## Implementation Risks
- **Context Unwrapping**: `getActivity()` uses a loop to unwrap `ContextWrapper`. C++ implementation must ensure it has a reliable way to reach the parent activity or window manager.
- **Resource Loading**: The button relies on themed attributes (`mediaRouteButtonStyle`) and system drawables. C++ layer must provide a robust resource lookup mechanism.
- **Performance**: Constant discovery (`CALLBACK_FLAG_PASSIVE_DISCOVERY`) can be battery-intensive. The C++ implementation should be mindful of discovery frequency.
