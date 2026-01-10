# WindowInfosListener - Reverse Engineering Documentation

## Executive Summary
`WindowInfosListener` is a base class for receiving real-time updates from `SurfaceFlinger` about the state of all windows on the system. It provides Z-ordered window handles and display metadata. It is a critical component for features like accessibility, screen recording, and global drag-and-drop.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `abstract class`
*   **Role**: Native Event Observer.
*   **Inner Class**: `DisplayInfo`.

## Detailed Functionality

### Native Bridge
*   Uses JNI (`nativeCreate`, `nativeRegister`, `nativeUnregister`) to hook into the SurfaceFlinger event pipeline.
*   `mNativeListener`: Holds a `long` pointer to the native listener object.
*   Uses `NativeAllocationRegistry` for native memory lifecycle management.

### Callbacks
*   `onWindowInfosChanged(...)`: Dispatched when any window moves, resizes, or changes visibility. Provides `InputWindowHandle[]` and `DisplayInfo[]`.

### DisplayInfo (Inner)
Captures logical display ID, dimensions (`Size`), and the display transform (`Matrix`).

## Java-to-C++ Translation Guide

### Native Integration
*   The Java class is a wrapper for a native listener.
*   C++ equivalent: `android::gui::WindowInfosListener`.
*   Translation involves using the native listener interface directly in C++ rather than through JNI.

### Data Types
*   `InputWindowHandle` -> `android::gui::WindowInfo`.
*   `Matrix` -> `android::ui::Transform` or `android::graphics::Matrix`.

## Implementation Risks
*   **Performance**: These callbacks are frequent and contain large arrays. C++ implementation should avoid unnecessary copying.
*   **Permission**: Requires `ACCESS_SURFACE_FLINGER`.
