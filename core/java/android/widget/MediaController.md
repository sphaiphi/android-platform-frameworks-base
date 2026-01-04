# MediaController - Reverse Engineering Documentation

## Executive Summary
`MediaController` is a floating view containing media playback controls (Play, Pause, Rewind, FF, Seek). It automatically integrates with a `MediaPlayerControl` interface.

## Architecture Overview
*   **Inheritance**: `FrameLayout` -> `MediaController`.
*   **Role**: Media UI Overlay.
*   **Window**: Creates its own `PhoneWindow` (floating panel) to display itself on top of the activity.

## Detailed Functionality
*   **Controls**: Contains buttons for standard media actions and a `SeekBar` for progress.
*   **Auto-Hide**: Uses a handler to hide itself after 3 seconds of inactivity.
*   **Anchor**: `setAnchorView` determines where the floating window appears.
*   **Update Loop**: `mShowProgress` runnable updates the seek bar and time text every second.

## Java-to-C++ Translation Guide
*   **Floating Window**: In C++, this might be implemented as a HUD overlay rather than a full system window.
*   **Interface**: Needs a `MediaPlayerControl` C++ abstract class.

## Implementation Risks
*   **Window Leaks**: Managing the lifecycle of the floating window relative to the activity.
