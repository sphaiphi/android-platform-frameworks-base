# DreamService - Reverse Engineering Documentation

## Executive Summary
`DreamService` is the base class for implementing custom Android screen savers (Daydreams). It provides a full-screen window for interactive content that appears when the device is charging and idle, or docked. It also supports "dozing" for low-power ambient display modes.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service` and implements `Window.Callback`.
*   **Hosting**: In most cases, it uses a helper `DreamActivity` to host its window, allowing it to behave like a regular Activity for input and lifecycle management.
*   **IPC**: Implements `IDreamService.Stub` (via `DreamServiceWrapper`) to receive commands from the `DreamManagerService` in the system server.
*   **Lifecycle Hooks**:
    1.  `onAttachedToWindow()`: Called when the window is created. Use for `setContentView()`.
    2.  `onDreamingStarted()`: Called when animations should start.
    3.  `onDreamingStopped()`: Called when animations should stop.
    4.  `onDetachedFromWindow()`: Final cleanup.
*   **Permission**: Requires `android.permission.BIND_DREAM_SERVICE`.

## Detailed Functionality

### Core Configuration
*   **`setInteractive(boolean)`**: If false (default), any touch or key event wakes the device. If true, events are dispatched to the dream's window.
*   **`setFullscreen(boolean)`**: Controls `FLAG_FULLSCREEN`.
*   **`setScreenBright(boolean)`**: Controls `FLAG_KEEP_SCREEN_ON`.

### Dozing (Ambient Display)
*   **`startDozing()`**: Transitions the device into a low-power state. The screen remains on but the AP can suspend.
*   **`setDozeScreenState(int)`**: Sets the power mode (e.g., `Display.STATE_DOZE`, `STATE_DOZE_SUSPEND`).
*   **`setDozeScreenBrightness(int)`**: Adjusts screen brightness during doze.

### Dream Overlay
*   Recent Android versions support a `DreamOverlayService` that can draw on top of the dream. `DreamService` manages this connection via `DreamOverlayConnectionHandler`.

### Input Handling
*   Implements `dispatchKeyEvent`, `dispatchTouchEvent`, etc. Non-interactive dreams intercept these to trigger `wakeUp()`.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.dreams.DreamService"`
*   `DREAM_META_DATA`: `"android.service.dream"` - Points to an XML resource for settings.

## Java-to-C++ Translation Guide

### Windowing
*   **Java**: Uses `android.view.Window` and `WindowManager`.
*   **C++**: Requires interaction with `SurfaceControl` and `WindowManager` service if implementing a native dream. The `DreamService` itself is high-level; a C++ implementation might focus on the `DreamManager` or the `DreamController` logic in the system server.

### IPC
*   **AIDL**: `IDreamService`, `IDreamManager`.

### Threading
*   **Java**: Uses `WakefulHandler` (wrapping a `PartialWakeLock`) to ensure work isn't suspended during doze.
*   **C++**: Must handle power management/wakelocks carefully if performing background work during doze.

## Implementation Risks
*   **Power Consumption**: Doze mode is critical for battery life. Dreams must minimize CPU/GPU usage when dozing.
*   **Security**: Dreams run over the keyguard. `FLAG_SHOW_WHEN_LOCKED` is used.
*   **Windowless Mode**: Some system-level dreams run without a full activity (`mWindowless`), requiring different surface management.
