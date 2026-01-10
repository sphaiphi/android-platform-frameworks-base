# WindowConfiguration - Reverse Engineering Documentation

## Executive Summary
`WindowConfiguration` encapsulates all the window-related settings and state for a window container (Activities, Tasks, Displays, etc.). It tracks physical bounds, app-usable bounds, rotation, windowing mode (Fullscreen, PiP, Freeform), and activity type (Home, Assistant, Recents). This class is fundamental to the window manager's ability to calculate layouts and manage multitasking.

## Architecture Overview
- **Core Components**:
    - **Bounds**: `mBounds` (actual physical area), `mAppBounds` (area usable by app after insets), `mMaxBounds` (maximum potential area).
    - **Rotation**: `mRotation` (relative to display), `mDisplayRotation` (apparent display orientation).
    - **Modes**: `mWindowingMode` (logical state), `mActivityType` (functional role).
    - **Priority**: `mAlwaysOnTop`.
- **Inheritance**: Implements `Parcelable` and `Comparable`.
- **Serialization**: Supports both standard `Parcel` and ProtoBuf (`WindowConfigurationProto`) for system-level logging and tracing.

## Detailed Functionality

### Bounds Management
**Purpose**: Defining the window geometry.
**Logic**: Tracks multiple Rects to handle complex scenarios like letterboxing or multi-window display where the app's usable area differs from its parent's bounds.

### Windowing Modes
**Purpose**: Dictating behavior and placement.
- `FULLSCREEN`: Standard single-app mode.
- `PINNED`: Picture-in-Picture.
- `FREEFORM`: Desktop-like resizable windows.
- `MULTI_WINDOW`: Split-screen or other shared layouts.

### Activity Types
**Purpose**: System-level role identification.
- `HOME`: Launcher activities.
- `RECENTS`: Overview/Task switcher.
- `ASSISTANT`: Search or voice assistants.
- `DREAM`: Screensavers.

### Configuration Merging (`updateFrom`)
**Purpose**: Hierarchical state propagation.
**Algorithm**: Copies non-default/defined fields from a "delta" configuration into the current one, returning a bitmask of changed fields (e.g., `WINDOW_CONFIG_BOUNDS`).

## API Reference
- `public @WindowingMode int getWindowingMode()`: Returns current mode.
- `public @ActivityType int getActivityType()`: Returns role.
- `public Rect getBounds()`: Returns physical area.
- `public int updateFrom(WindowConfiguration delta)`: Merges new state.

## Java-to-C++ Translation Guide
- **Rect Mapping**: Use `android::graphics::Rect` in the native layer.
- **Enum Mapping**: Use C++ `enum class` for modes and types.
- **Bitmasks**: Replicate the `WINDOW_CONFIG_...` constants for change tracking.
- **ProtoBuf**: Use native C++ ProtoBuf headers generated from `WindowConfigurationProto` for serialization.

## Implementation Risks
- **Identity Consistency**: The logic for `isAlwaysOnTop()` and `canReceiveKeys()` must be perfectly synchronized with the system server's window policy.
- **Parcel Alignment**: Standard parceling and ProtoBuf serialization must match the system definitions exactly to avoid communication failures between `WindowManager` and client processes.
- **Complexity**: Handling the interaction between `mRotation` and `mDisplayRotation` during bounds calculation is non-trivial and orientation-dependent.
