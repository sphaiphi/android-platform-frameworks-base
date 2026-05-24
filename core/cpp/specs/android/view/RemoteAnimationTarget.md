# RemoteAnimationTarget - Reverse Engineering Documentation

## Executive Summary
`RemoteAnimationTarget` is a comprehensive descriptor of a single window or task participating in a remote animation. It provides all the necessary information (leashes, bounds, insets, window configuration) for a remote process to visually animate that window.

## Data Model

### 1. Identity
*   **`taskId`**: The ID of the task.
*   **`mode`**: Whether the app is opening (`MODE_OPENING`), closing (`MODE_CLOSING`), or changing (`MODE_CHANGING`).

### 2. Surfaces
*   **`leash`**: `SurfaceControl` - The primary handle for animating the window.
*   **`startLeash`**: Optional handle for the starting state in change transitions.

### 3. Geometry
*   **`screenSpaceBounds`**: The final physical location on screen.
*   **`startBounds`**: The initial physical location.
*   **`contentInsets`**: System bar regions.

### 4. Metadata
*   **`isTranslucent`**: Whether the app shows content behind it.
*   **`windowConfiguration`**: Full display/bounds info from the system.

## Detailed Functionality
*   **Parcelable**: This is the primary data unit passed to `IRemoteAnimationRunner.onAnimationStart()`.
*   **Z-Ordering**: `prefixOrderIndex` (Deprecated) was used to guide layer placement.

## Java-to-C++ Translation Guide
*   **Primary Mapping**: Map to `android::view::RemoteAnimationTarget`.
*   **Parceling**: Serialization MUST match the native implementation in `frameworks/native/libs/gui/`.

## Implementation Risks
*   **Surface Lifecycle**: The `leash` is a powerful handle; the remote process must not call `release()` until the transition is complete and it has handed back control.
*   **Coordinate Systems**: Animatorts must correctly account for the difference between `localBounds` (relative to parent) and `screenSpaceBounds`.
