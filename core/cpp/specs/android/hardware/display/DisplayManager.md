# DisplayManager - Reverse Engineering Documentation

## Executive Summary
`DisplayManager` is the primary high-level API for interacting with the Android display system. It allows applications to query attached displays (`getDisplays`), monitor for changes (`registerDisplayListener`), create virtual displays (`createVirtualDisplay`), and manage Wi-Fi display connections.

## Architecture Overview
- **Pattern**: Facade / Manager.
- **Backing Service**: `IDisplayManager` (via `DisplayManagerGlobal`).
- **Key Concepts**:
    - **Logical Display**: Represented by `android.view.Display`. The high-level view of a screen area (which might map to a physical screen, a virtual screen, or a part of a screen).
    - **Virtual Display**: A display backed by a Surface, created by an app.
    - **Wifi Display (Miracast)**: Wireless external displays.

## Detailed Functionality

### Display Enumeration
- `getDisplay(int displayId)`: Returns a `Display` object. Uses a weak cache (`WeakDisplayCache`) to recycle objects.
- `getDisplays(String category)`: Returns list of displays filtering by category (Presentation, Built-in, Rear, etc.).

### Event Listening
- `registerDisplayListener`: Delegates to `DisplayManagerGlobal`.
- Events: Added, Removed, Changed, Refresh Rate Changed, Brightness Changed (Private), HDR/SDR Ratio Changed (Private).

### Virtual Displays
- `createVirtualDisplay`: Complex builder-based creation.
- Flags: Public/Private, Secure, Auto-Mirror, Own-Content-Only, etc.
- **Mechanism**: Calls `mGlobal.createVirtualDisplay`, which calls the system service. The service returns a `displayId`, which is wrapped in a `VirtualDisplay` object.

### Wi-Fi Display
- Methods like `connectWifiDisplay`, `startWifiDisplayScan` delegate to Global. These require specific permissions.

### Brightness & HDR
- Methods to set/get brightness, brightness configuration (adaptive brightness curves), and HDR conversion modes.
- Many methods require `CONTROL_DISPLAY_BRIGHTNESS` or `CONFIGURE_DISPLAY_BRIGHTNESS`.

### Display Topology
- **Topology**: Defines relative positioning of displays.
- `setDisplayTopology` / `registerTopologyListener`.

## Data Model
- **Cache**: `WeakDisplayCache` (SparseArray of WeakReferences) to ensure object identity or reduce allocation? (Code comments say cache is currently disabled via `DisplayManagerGlobal.USE_CACHE`, but `DisplayManager` has its own `mDisplayCache`). *Correction: `DisplayManager` has a `WeakDisplayCache`, `DisplayManagerGlobal` has a `PropertyInvalidatedCache`*.

## Java-to-C++ Translation Guide
- This class is very Java-centric, relying on `Context`, `Handler`, `Surface`, and `Executor`.
- **C++ Client**: A C++ equivalent would wrap `IDisplayManager` (Binder interface).
- **Callbacks**: Java callbacks use `Handler`/`Executor`. C++ callbacks typically happen on a binder thread or need a `Looper`.
- **Virtual Display**: In C++, this involves passing an `IGraphicBufferProducer` (Surface) to the SurfaceFlinger/DisplayManager.

## Risks & Notes
- **Hidden APIs**: Significant amount of functionality (Wi-Fi display, Brightness Config) is `@hide` or `@SystemApi`.
- **Flags**: Heavy use of `FeatureFlags` (`Flags.FLAG_...`) to toggle new APIs.
