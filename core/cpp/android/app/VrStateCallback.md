# VrStateCallback - Reverse Engineering Documentation

## Executive Summary
`VrStateCallback` is an abstract base class used to receive notifications about changes in the device's Virtual Reality (VR) state. It defines hooks for both standard VR mode transitions and persistent VR mode changes. It is used in conjunction with the `VrManager`.

## Architecture Overview
- **Structure**: Abstract class with no-op default implementations for callbacks.
- **Visibility**: Marked as `@hide` and `@SystemApi`.

## Detailed Functionality

### Event Hooks
- `onVrStateChanged(boolean enabled)`: Triggered when the system enters or exits VR mode.
- `onPersistentVrStateChanged(boolean enabled)`: Triggered when the persistent VR mode status changes.

## API Reference
- `public void onVrStateChanged(boolean enabled)`
- `public void onPersistentVrStateChanged(boolean enabled)`

## Java-to-C++ Translation Guide
- **Callback Interface**: Map to a C++ abstract class or an interface.
- **Integration**: Subclasses in C++ will override these methods to perform native logic, such as pausing/resuming GPU-intensive rendering or adjusting the UI for VR viewing.

## Implementation Risks
- **Threading**: Callbacks are dispatched via an `Executor`. C++ implementation must ensure thread safety when reacting to state changes that affect shared resources.
