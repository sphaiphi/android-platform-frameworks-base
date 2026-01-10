# RemoteAnimationAdapter - Reverse Engineering Documentation

## Executive Summary
`RemoteAnimationAdapter` describes how a remote animation (an animation controlled by another process, like the Launcher) should be executed. It carries the runner interface, timing information, and metadata about the transition requirements.

## Data Model
*   **`mRunner`**: `IRemoteAnimationRunner` - The binder callback that WMS invokes to start the animation.
*   **`mDuration`**: `long` - The total expected time for the transition.
*   **`mStatusBarTransitionDelay`**: `long` - How long to wait before animating system bars.
*   **`mCallingApplication`**: `IApplicationThread` - The process that will execute the animation.

## Detailed Functionality
*   **Control**: Used by `WindowManager.overridePendingAppTransitionRemote()` to hand off transition control to a third-party app.
*   **Identity Tracking**: System server uses `setCallingPidUid()` to track the origin of the runner.

## Java-to-C++ Translation Guide
*   **IPC**: Marshalling must be compatible with `frameworks/native/libs/gui/`.
*   **Runners**: In C++, the runner implementation will likely involve `android::SurfaceControl::Transaction` for animating leashes.

## Implementation Risks
*   **ANR**: If the remote process fails to signal completion via the finished callback, the system transition will hang until it times out.
*   **Security**: The system must verify that the process providing the adapter has permission to control app transitions.
