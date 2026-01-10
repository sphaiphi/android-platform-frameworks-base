# ScreenCapture - Reverse Engineering Documentation

## Executive Summary
`ScreenCapture` provides a static API for capturing the screen or specific surface layers. It acts as a high-level wrapper around the native surface composition engine (SurfaceFlinger) capture capabilities.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class`
*   **Role**: API Facade / Native Wrapper.
*   **JNI**: Heavily relies on native methods.

## Data Model

### `CaptureArgs` (Parcelable)
Base class for capture arguments.
*   `mPixelFormat`, `mSourceCrop`, `mFrameScale`, `mCaptureSecureLayers`, `mUid`, `mGrayscale`, `mExcludeLayers`.

### `DisplayCaptureArgs` extends `CaptureArgs`
*   `mDisplayToken`: IBinder.
*   `mWidth`, `mHeight`.

### `LayerCaptureArgs` extends `CaptureArgs`
*   `mNativeLayer`: Pointer to SurfaceControl.
*   `mChildrenOnly`.

### `ScreenshotHardwareBuffer`
Wraps a `HardwareBuffer` with `ColorSpace` and metadata (secure, HDR).

## Detailed Functionality

### `captureDisplay` / `captureLayers`
*   Constructs `Args`.
*   Calls `nativeCapture...`.
*   Can be synchronous (`SynchronousScreenCaptureListener`) or asynchronous (`ScreenCaptureListener`).

### `SynchronousScreenCaptureListener`
*   Uses a `CountDownLatch` to wait for the callback from native code.
*   Timeout: 4 seconds (scaled by multiplier).

## Java-to-C++ Translation Guide

### JNI Reverse Direction
*   This Java code *calls* C++.
*   In C++, you would interface directly with `SurfaceComposerClient::screenshot` or the ISurfaceComposer AIDL/HIDL interface.
*   The `CaptureArgs` parcelables likely map to structs in `gui/LayerState.h` or similar in the native framework.

## Implementation Risks
*   **Blocking**: The synchronous capture blocks the calling thread. In C++, ensure this doesn't happen on the UI thread or critical binder threads if avoided.
*   **HardwareBuffer**: Accessing `HardwareBuffer` in C++ (`AHardwareBuffer`) is standard.
