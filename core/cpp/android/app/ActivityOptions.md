# ActivityOptions - Reverse Engineering Documentation

## Executive Summary
`ActivityOptions` is a helper class to build a `Bundle` options object used to customize how an Activity is started. It controls animations, transition types, and target displays.

## Architecture Overview
*   **Inheritance**: `ComponentOptions`.
*   **Data Storage**: Stores configuration in a `Bundle`.

## Detailed Functionality

### Animations
*   `makeCustomAnimation(Context, int enterResId, int exitResId)`: Custom resource animations.
*   `makeScaleUpAnimation(View, int, int, int, int)`: Scales up from a specific screen area.
*   `makeThumbnailScaleUpAnimation`: Scales from a bitmap.
*   `makeSceneTransitionAnimation`: Shared element transitions.

### Launch Configuration
*   `setLaunchDisplayId(int)`: Target display.
*   `setLaunchWindowingMode(int)`: Split-screen, Freeform, etc.
*   `setLockTaskEnabled(boolean)`: Start in Lock Task mode.

### Implementation Details
*   Serializes internal state (animation type, resource IDs, shared element names, bounds) into the `Bundle` with specific keys (`android:activity.animType`, etc.).

## Java-to-C++ Translation Guide
*   **Bundle Creation**: Needs a mechanism to create the equivalent of a `Bundle` (map of variants) to pass to the IPC interface.
*   **Animation Constants**: Maps to `ANIM_` constants.

## Implementation Risks
*   **Compatibility**: Ensuring the keys and values match what the system server expects.
