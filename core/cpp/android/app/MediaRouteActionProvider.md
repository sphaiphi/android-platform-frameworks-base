# MediaRouteActionProvider - Reverse Engineering Documentation

## Executive Summary
`MediaRouteActionProvider` is a specialized `ActionProvider` that displays a `MediaRouteButton` in the application's `ActionBar`. It allows users to select media routes (like Chromecast or Bluetooth speakers) and control the currently selected route. It automatically manages the visibility of the menu item based on whether matching routes are available.

## Architecture Overview
- **Inheritance**: Extends `ActionProvider`.
- **Core Components**:
    - `MediaRouter mRouter`: System service for managing media routes.
    - `MediaRouteButton mButton`: The actual UI component displayed in the menu.
    - `MediaRouterCallback mCallback`: Internal listener for route changes (additions, removals, state changes).
- **Management**: Tracks the requested `routeTypes` and updates the UI dynamically.

## Detailed Functionality

### setRouteTypes(int types)
**Purpose**: Specifies the types of routes (e.g., `ROUTE_TYPE_LIVE_AUDIO`) that the user should be allowed to select.
**Algorithm**:
1. If the types have changed, removes the previous callback from `mRouter`.
2. Adds a new `mCallback` for the new types using `CALLBACK_FLAG_PASSIVE_DISCOVERY`.
3. Calls `refreshRoute()` to update visibility and the button's internal state.

### onCreateActionView(MenuItem item)
**Purpose**: Creates the `MediaRouteButton` instance to be shown in the menu.
**Algorithm**:
1. Instantiates a new `MediaRouteButton`.
2. Configures it with the current `mRouteTypes` and `mExtendedSettingsListener`.
3. Sets layout parameters to match the action bar height.

### isVisible()
**Purpose**: Overrides the default item visibility.
**Logic**: Returns `true` if `mRouter.isRouteAvailable` indicates that at least one route matching the requested types is currently discoverable.

## API Reference
- `public void setRouteTypes(int types)`: Configures filtered route types.
- `public void setExtendedSettingsClickListener(View.OnClickListener listener)`: Attaches a custom listener for the settings button in the route chooser dialog.
- `public View onCreateActionView(MenuItem item)`: Factory method for the UI button.

## Java-to-C++ Translation Guide
- **ActionProvider Framework**: If using a native C++ UI framework for the action bar, implement a provider interface that handles view creation and visibility updates.
- **MediaRouter Service**: Communicate with the `media_router` system service via its AIDL interface.
- **Callback Handling**: Use a `std::weak_ptr` pattern for the callback to avoid memory leaks, as highlighted by the `FIXME` comment in the Java source regarding callback leaks.

## Implementation Risks
- **Callback Leaks**: The Java implementation notes a risk of leaking callbacks because there is no clear signal when the `ActionProvider` is no longer needed by the UI. C++ implementation should use RAII or explicit cleanup in the destructor to ensure `removeCallback` is called.
- **UI State Sync**: Ensuring the button correctly reflects the active route state (connecting vs. connected) requires tight integration with the `MediaRouter` state machine.
