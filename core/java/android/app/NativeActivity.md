# NativeActivity - Reverse Engineering Documentation

## Executive Summary
`NativeActivity` is a specialized `Activity` that allows developers to implement their application's logic almost entirely in native C/C++ code. It handles the bridging between the Android framework lifecycle events and a set of native callbacks (using the Android NDK). It provides direct access to a `Surface` for rendering and an `InputQueue` for handling user input.

## Architecture Overview
- **Inheritance**: Extends `Activity`.
- **Interfaces**: Implements `SurfaceHolder.Callback2`, `InputQueue.Callback`, and `OnGlobalLayoutListener`.
- **Core Components**:
    - `NativeContentView`: A custom `View` that acts as the container for the native rendering.
    - `mNativeHandle`: A long integer storing the pointer to the native `ANativeActivity` structure.
    - **Native Methods**: Extensive use of `native` methods to notify the C++ layer of lifecycle and window state changes.

## Detailed Functionality

### onCreate(Bundle savedInstanceState)
**Purpose**: Initializes the native activity by loading the shared library and establishing the native handle.
**Algorithm**:
1. Configures the window to "take" the surface and input queue from this activity.
2. Creates and sets a `NativeContentView`.
3. Retrieves metadata (`android.app.lib_name`, `android.app.func_name`) from the manifest to identify the shared library and entry point.
4. Uses `BaseDexClassLoader` to find the library path.
5. Calls `loadNativeCode(...)`, which is a native method that executes the native entry point and returns a handle.
6. Throws an error if the library cannot be loaded or initialized.

### Lifecycle Forwarding (`onPause`, `onResume`, `onStart`, `onStop`, `onDestroy`)
**Purpose**: Proxies Java-side lifecycle events to the native code.
**Mechanism**: Each method calls a corresponding `on...Native(mNativeHandle)` method. For example, `onPause()` calls `onPauseNative(mNativeHandle)`.

### Window and Input Management
- `surfaceCreated`, `surfaceChanged`, `surfaceDestroyed`: Notifies native code of surface lifecycle changes using `onSurface...Native`.
- `onInputQueueCreated`, `onInputQueueDestroyed`: Notifies native code when the `InputQueue` is ready for consumption.
- `onGlobalLayout`: Monitors changes in the content view's position or size and notifies native code via `onContentRectChangedNative`.

### JNI Bridge
The class defines several private native methods that map to the NDK `ANativeActivityCallbacks` structure:
- `loadNativeCode`, `unloadNativeCode`
- `onStartNative`, `onResumeNative`, `onSaveInstanceStateNative`, etc.
- `onSurfaceCreatedNative`, `onInputQueueCreatedNative`, etc.

## API Reference
- `public static final String META_DATA_LIB_NAME`: Key for library name in manifest.
- `public static final String META_DATA_FUNC_NAME`: Key for entry point function name.
- `void showIme(int mode)`: Internal helper to show the soft keyboard.
- `void hideIme(int mode)`: Internal helper to hide the soft keyboard.

## Java-to-C++ Translation Guide
- **Native Handle**: The `mNativeHandle` corresponds to a pointer to an `ANativeActivity` structure in the NDK.
- **Entry Point**: The default function name is `ANativeActivity_onCreate`.
- **Event Loop**: Native code typically runs its own event loop in a separate thread, waiting for messages from the `InputQueue` and lifecycle events from the framework.
- **Surface Rendering**: Rendering is done via `ANativeWindow`, which is the native counterpart to Java's `Surface`.

## Implementation Risks
- **Synchronization**: Lifecycle events arrive on the main UI thread, while the native application often runs on its own thread. Proper synchronization (using mutexes or a thread-safe message queue) is essential to avoid race conditions during surface destruction.
- **Memory Management**: The `mNativeHandle` must be carefully managed to ensure `unloadNativeCode` is called once and only once during `onDestroy`.
- **Error Handling**: Failures in `loadNativeCode` are fatal and must provide descriptive errors (via `getDlError()`).
