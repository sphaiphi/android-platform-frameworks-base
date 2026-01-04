# WidgetFlags - Reverse Engineering Documentation

## Executive Summary
`WidgetFlags` is a utility class that defines string constants and default values for feature flags managed via `android.provider.DeviceConfig`. These flags allow for server-side control over specific UI behaviors and experimental features within the "widget" namespace (primarily affecting `TextView`, `EditText`, and `AnalogClock`).

## Architecture Overview
- **Role**: Configuration / Feature Toggle constants.
- **Namespace**: `android.provider.DeviceConfig.NAMESPACE_WIDGET` ("widget").
- **Core Setting Keys**: These keys are typically used to sync device configuration into application "Core Settings" during process startup or when a config change occurs.

## Detailed Functionality

### Cursor and Selection Controls
- **`ENABLE_CURSOR_DRAG_FROM_ANYWHERE`**: Enables or disables the ability to start a cursor drag by swiping anywhere on the text, not just on the handle.
- **`CURSOR_DRAG_MIN_ANGLE_FROM_VERTICAL`**: Defines the swipe angle threshold (0-90 degrees) to distinguish between a scroll gesture (vertical) and a cursor drag gesture (horizontal). Default is 45 degrees.
- **`FINGER_TO_CURSOR_DISTANCE`**: Specifies a custom vertical offset (in DP) between the user's finger and the cursor during a drag operation.
- **`ENABLE_INSERTION_HANDLE_GESTURES`**: Enables additional interactions like long-press or double-tap on the cursor handle.

### Insertion Handle Appearance
- **`INSERTION_HANDLE_DELTA_HEIGHT`**: Adjusts the height of the cursor handle.
- **`INSERTION_HANDLE_OPACITY`**: Sets the alpha (0-100) of the handle.

### Magnifier Configuration
- **`ENABLE_NEW_MAGNIFIER`**: Toggles between the legacy magnifier and a newer implementation.
- **`MAGNIFIER_ZOOM_FACTOR`**: Controls the zoom level (default 1.5x).
- **`MAGNIFIER_ASPECT_RATIO`**: Controls the width-to-height ratio of the magnifier window (default 5.5).

### Analog Clock
- **`ANALOG_CLOCK_SECONDS_HAND_FPS`**: Controls the frame rate for the seconds hand animation in the `AnalogClock` widget.

## Data Model

| Flag Category | Keys | Type / Default |
|---------------|------|----------------|
| Cursor Drag | `enable_cursor_drag_from_anywhere` | `boolean` (true) |
| Swipe Angle | `min_angle_from_vertical_to_start_cursor_drag` | `int` (45) |
| Magnifier Zoom| `magnifier_zoom_factor` | `float` (1.5f) |
| Clock FPS | `analog_clock_seconds_hand_fps` | `int` (Dynamic) |

## Java-to-C++ Translation Guide

### Configuration Access
- **DeviceConfig**: The C++ implementation must have a mechanism to query the `DeviceConfig` service. In Android, this is usually done via a Binder call to the `SettingsProvider`.
- **CoreSettings**: During initialization, the `ActivityThread` (Java) pushes these values into `CoreSettings`. The C++ framework should implement a similar mechanism where a global configuration object is updated when these flags change.

### Constants Management
- **Headers**: These strings should be placed in a C++ header file (e.g., `WidgetFlags.h`) within an `android::widget` namespace.

```cpp
namespace android::widget {
class WidgetFlags {
public:
    static constexpr const char* ENABLE_CURSOR_DRAG_FROM_ANYWHERE = "CursorControlFeature__enable_cursor_drag_from_anywhere";
    // ...
};
}
```

## Implementation Risks
- **Range Validation**: Some flags (like angle and opacity) have specific valid ranges (0-90, 0-100). The C++ code that *consumes* these flags must perform defensive range-checking as noted in the Java comments.
- **Default Discrepancies**: Ensure that the default values in C++ exactly match those in Java to avoid inconsistent behavior across processes or platform versions.
- **Unit Units**: Note that many values are in **DP** (Density-independent Pixels). The C++ code must use the device's display density to convert these to raw pixels before application.
