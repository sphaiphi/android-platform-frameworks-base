# UiModeManager - Reverse Engineering Documentation

## Executive Summary
`UiModeManager` provides access to system-level UI mode services. It allows applications to control and respond to different operational modes of the device, such as car mode (driving), desk mode (docked), and night mode (dark theme). It also manages UI contrast settings and handles "projections" (e.g., automotive projection).

## Architecture Overview
- **Service Integration**: Managed by `SystemServiceRegistry` and accessible via `Context.UI_MODE_SERVICE`.
- **Backend Communication**: Acts as a client wrapper for the `IUiModeManager` AIDL interface.
- **Inner Classes**:
    - `Globals`: A singleton callback stub that receives updates from the system server regarding contrast and force-invert state changes.
    - `ContrastUtils`: Utility for converting between float contrast values and discrete levels.
    - `InnerListener`: A Binder proxy for projection state changes.
- **Caching**: Uses `IpcDataCache` to locally store the current mode type and night mode status to reduce IPC overhead.

## Detailed Functionality

### Mode Management
- **Car Mode**: Apps can enable car mode with a specific priority. Higher priority apps take precedence for features like `InCallService` routing.
- **Night Mode**: Supports `AUTO` (time-based), `CUSTOM` (user-defined schedule), `BEDTIME`, and manual `YES`/`NO` settings. Changes trigger configuration updates across all apps.

### UI Contrast and Accessibility
**Mechanism**:
- `getContrast()`: Returns a value in `[-1.0, 1.0]`.
- `addContrastChangeListener`: Allows apps to adapt their custom rendering to the system contrast setting.
- **Force Invert**: Manages the system-wide "force dark" status for apps.

### Projections (`requestProjection`)
**Purpose**: Specialized modes for external displays or integration (e.g., Android Auto).
**Logic**: Tracks which packages are projecting and notifies listeners of state changes.

## API Reference (Key Methods)
- `public void enableCarMode(int flags)`: Enters driving mode.
- `public void setNightMode(int mode)`: Configures dark theme.
- `public float getContrast()`: Retrieves user preference.
- `public void requestProjection(int projectionType)`: Enters a projection mode.

## Java-to-C++ Translation Guide
- **AIDL Integration**: Use AIDL-generated C++ interface `android::app::IUiModeManager`.
- **Configuration Mapping**: Map `Configuration.UI_MODE_TYPE_...` constants to C++ equivalents.
- **Cache Implementation**: Replicate `IpcDataCache` using native property-invalidated cache patterns.
- **Listener Management**: Use a C++ observer pattern with `std::function` and handle registration/unregistration with the system service.

## Implementation Risks
- **Config Update Storms**: Changing night mode affects every process. C++ implementation must handle `onConfigurationChanged` efficiently.
- **Priority Conflicts**: Multiple apps requesting car mode with different priorities must be resolved correctly by the system server logic.
- **Binder Latency**: Although cached, some methods perform synchronous IPC. C++ callers should be aware of potential blocking.
