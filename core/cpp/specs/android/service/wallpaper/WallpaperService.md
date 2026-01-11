# WallpaperService - Reverse Engineering Documentation

## Executive Summary
`WallpaperService` is the base class for implementing live wallpapers in Android. It provides a drawing surface that sits behind all other application windows and manages the lifecycle of the wallpaper's rendering engine. It also facilitates interaction with the system for features like parallax scrolling, UI theming (via color extraction), and low-power ambient display modes.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **Engine-Based Model**: The service itself is a factory for `Engine` instances. Each instance represents a specific wallpaper view (e.g., active wallpaper, preview, or on a different display).
*   **IPC**: Implements `IWallpaperService.Stub`. It interacts with the `WallpaperManagerService` in the system server and receives surface control from the `WindowManager`.
*   **Rendering**: Wallpapers draw to a `Surface` provided by the system. They can use the `Canvas` API or hardware-accelerated APIs like OpenGL/Vulkan.
*   **Permission**: Requires `android.permission.BIND_WALLPAPER`.

## Detailed Functionality

### `Engine` (Abstract Inner Class)
The `Engine` is where the actual work happens.
*   **Lifecycle**:
    *   `onCreate(SurfaceHolder)`: Initial setup.
    *   `onVisibilityChanged(boolean)`: Crucial for performance; animations should stop when the wallpaper is not visible.
    *   `onOffsetsChanged(...)`: Called when the user swipes between launcher pages to implement parallax effects.
    *   `onSurfaceCreated` / `onSurfaceChanged` / `onSurfaceDestroyed`: Standard surface management.
*   **Interaction**:
    *   `onTouchEvent(MotionEvent)`: Receives touch events if enabled via `setTouchEventsEnabled(true)`.
    *   `onCommand(...)`: Receives generic commands from the system or launcher (e.g., `COMMAND_TAP`).
*   **Theming & Colors**:
    *   `onComputeColors()`: The service should return the primary colors of the wallpaper. The system uses these for Material You dynamic theming.
    *   `notifyLocalColorsChanged(...)`: Provides color information for specific regions of the screen.

### Ambient Mode (AOD)
*   **`onAmbientModeChanged(boolean, long)`**: Notifies the engine to switch to a low-power, high-contrast visual style for Always-On Display.

### Performance & Throttling
*   Includes internal rate-limiting for color extraction (`NOTIFY_COLORS_RATE_LIMIT_MS`).
*   Uses `BLASTBufferQueue` for efficient buffer management in modern Android versions.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.wallpaper.WallpaperService"`
*   `SERVICE_META_DATA`: `"android.service.wallpaper"` - Points to an XML resource containing `<wallpaper>` tag.

## Java-to-C++ Translation Guide

### Windowing & Surfaces
*   **Java**: Uses `android.view.Surface` and `android.view.IWindowSession`.
*   **C++**: Requires `ANativeWindow` and interaction with `SurfaceComposer` (SurfaceFlinger client). Live wallpapers in C++ (if implemented as a system component) would be a `WindowlessWindowManager` or a direct `SurfaceControl` consumer.

### Threading
*   **Java**: The service uses a dedicated `HandlerCaller` and a background thread for color extraction.
*   **C++**: A dedicated rendering thread is essential to prevent blocking the main binder thread and to ensure smooth 60/120fps animations.

## Implementation Risks
*   **Battery Drain**: A poorly implemented live wallpaper is a primary cause of high battery usage. Use of `onVisibilityChanged` is mandatory.
*   **Memory Usage**: Large textures or frequent bitmap allocations can lead to OOM or system sluggishness.
*   **Concurrency**: Multiple `Engine` instances can exist. Shared resources (like OpenGL contexts or shared textures) must be handled carefully.
