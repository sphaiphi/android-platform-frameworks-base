# Presentation - Reverse Engineering Documentation

## Executive Summary
`Presentation` is a specialized `Dialog` subclass designed to present content on a secondary display (e.g., HDMI monitor, wireless display). It configures its own `Context` and resource configuration according to the secondary display's metrics, ensuring that layouts and assets are correctly sized. It is automatically cancelled when its target display is removed.

## Architecture Overview
- **Inheritance**: Extends `Dialog`.
- **Core Components**:
    - `mDisplay`: The target `Display` for the presentation.
    - `mDisplayManager`: System service used to monitor display lifecycle events.
    - `mHandler`: Used for handling display-related events on the creation thread.
- **Context Management**: Creates a "display context" using `createDisplayContext(display)` and a "window context" to ensure it operates in the correct coordinate space and density.

## Detailed Functionality

### Construction
**Purpose**: Sets up the presentation for a specific display.
**Algorithm**:
1. Creates a display context and a window context from the provided `outerContext` and `display`.
2. Resolves the appropriate theme (defaulting to `presentationTheme` if not specified).
3. Sets the window type to `TYPE_PRESENTATION` or `TYPE_PRIVATE_PRESENTATION` based on display flags.
4. Sets the window gravity to `Gravity.FILL`.

### Display Lifecycle Monitoring
**Purpose**: Ensures the presentation reacts to the status of its target display.
**Logic**:
- `onStart()`: Registers a `DisplayListener` with `DisplayManager`.
- `mDisplayListener`: Listens for `onDisplayRemoved` and `onDisplayChanged`.
- If the current `mDisplay` is removed, it automatically calls `cancel()`.

### Content Rendering
**Purpose**: Provides standard `Dialog` hooks but scoped to the secondary display.
**Algorithm**: Use `setContentView()` or `addContentView()` as normal. The `Resources` object returned by `getContext().getResources()` will be tuned to the secondary display's DPI and orientation.

## API Reference
- `public Display getDisplay()`: Returns the associated display.
- `public Resources getResources()`: Returns display-tuned resources.
- `public void show()`: Displays the presentation. Throws `InvalidDisplayException` if the display is not a presentation display.
- `public void onDisplayRemoved()`: Hook for cleanup when display is disconnected.
- `public void onDisplayChanged()`: Hook for handling resolution or density changes.

## Java-to-C++ Translation Guide
- **Display Management**: Use the NDK `ADisplayManager` or AIDL `IDisplayManager` to enumerate displays.
- **Window Creation**: Use `ASurfaceControl` and `ANativeWindow` to create a rendering surface on the secondary display. In C++, this involves establishing a connection with `SurfaceFlinger` and specifying the target display layer.
- **Resource Scaling**: Implement a resource management system that can load assets based on a specific `DisplayMetrics` struct.

## Implementation Risks
- **Context Mismatch**: Attempting to use UI components from the main activity's context on a `Presentation` surface will lead to incorrect scaling. C++ implementation must strictly isolate the rendering state for each display.
- **Multi-display Synchronization**: If content is mirrored or coordinated between displays, the C++ layer must handle synchronization of frame buffers and input events across different display threads.
