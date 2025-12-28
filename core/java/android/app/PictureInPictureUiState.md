# PictureInPictureUiState - Reverse Engineering Documentation

## Executive Summary
`PictureInPictureUiState` is a small data class used to communicate the current state of an activity in Picture-in-Picture (PiP) mode to the application. It provides information about whether the PiP window is "stashed" (partially hidden by the user) or if it's currently in the middle of a transition into PiP mode.

## Architecture Overview
- **Core Components**:
    - `mIsStashed`: A boolean indicating if the PiP window is stashed off-screen.
    - `mIsTransitioningToPip`: A boolean indicating if the enter-PiP animation is running.
- **Inheritance**: Implements `Parcelable`.
- **Builder Pattern**: Uses an internal `Builder` class for construction.

## Detailed Functionality

### Stash State
**Purpose**: Allows apps to react when the PiP window is moved off-screen.
**Usage**: If `isStashed()` is true, an app might choose to pause media playback or hide non-essential overlays.

### Transition State
**Purpose**: Provides a signal at the very beginning of the PiP entry.
**Usage**: When `isTransitioningToPip()` is true, apps are encouraged to hide their full-screen UI controls (like video seek bars) to ensure a clean animation into the small PiP window.

## API Reference
- `public boolean isStashed()`: Returns stash status.
- `public boolean isTransitioningToPip()`: Returns transition status.

## Java-to-C++ Translation Guide
- **Simple Struct**: Map to a simple `struct` or `class` in C++.
- **Parceling**: Implement `writeToParcel` and `readFromParcel` using the `Parcel` class in `libbinder`.

## Implementation Risks
- **Timing**: The `isTransitioningToPip` flag is transient. C++ implementations must ensure they handle this state change promptly before the window actually enters the PiP state machine in the system server.
