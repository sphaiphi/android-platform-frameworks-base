# ColorDisplayManager - Reverse Engineering Documentation

## Executive Summary
`ColorDisplayManager` is the system service surface for managing color transforms, Night Light (Night Display), and other display post-processing effects like Saturation and Display White Balance. It delegates IPC calls to `IColorDisplayManager` via an internal singleton helper `ColorDisplayManagerInternal`.

## Architecture Overview
- **Type**: Manager / System Service Wrapper
- **Package**: `android.hardware.display`
- **IPC Interface**: `IColorDisplayManager`
- **Internal Helper**: `ColorDisplayManagerInternal` (Singleton) ensures one connection per process.

## Detailed Functionality

### Night Display (Night Light)
- **Activation**: `setNightDisplayActivated(boolean)`.
- **Auto Mode**:
    - `DISABLED`: Manual only.
    - `CUSTOM_TIME`: Based on user-set start/end times.
    - `TWILIGHT`: Based on sunset/sunrise.
- **Configuration**:
    - `ColorTemperature`: Warmth of the display.
    - `CustomStartTime` / `CustomEndTime`.

### Color Modes & Transforms
- **Color Mode**: Natural, Boosted, Saturated, Automatic.
- **Saturation**: Global or Per-App saturation level (0-100).
- **Reduce Bright Colors (RBC)**: Accessibility feature to dim screen beyond hardware min.
- **Display White Balance**: Adapt display color to ambient light (True Tone equivalent).

### Capabilities
- **`getTransformCapabilities()`**: Returns bitmask (None, Protected Content, Global HW, Per-App HW).

## Data Model
- **Time**: Uses `android.hardware.display.Time` (custom Parcelable wrapping `LocalTime`).

## Java-to-C++ Translation Guide
- **IPC**: This class wraps Binder calls. C++ clients would typically use `IColorDisplayManager` directly via `binder_ndk` or C++ Binder.
- **Time**: The `Time` class is a simple hour/minute/second/nano struct.
- **Metrics**: Java code logs `MetricsEvent`. C++ implementation might need to hook into `statsd` or `atom` logging if it performs logic, but likely C++ just calls the service.

## API Reference
- `setNightDisplayActivated(boolean)`
- `setSaturationLevel(int)`
- `setColorMode(int)`
- `isNightDisplayAvailable(Context)`: Checks resources.

## Implementation Risks
- **Permission Checks**: Most methods require `CONTROL_DISPLAY_COLOR_TRANSFORMS`.
- **Concurrency**: The internal singleton uses synchronization.
