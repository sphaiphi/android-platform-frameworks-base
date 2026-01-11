# InputSettings - Reverse Engineering Documentation

## Executive Summary
`InputSettings` provides a centralized API for reading and writing input-related system settings (pointer speed, accessibility keys, touchpad gestures). It interacts with `Settings.System`, `Settings.Secure`, and `Settings.Global`.

## Architecture Overview
- **Utility Class**: All methods are static.
- **Feature Flags**: Uses `Flags` (from `com.android.hardware.input` and `com.android.input.flags`) to conditionally enable getters/setters.
- **Permissions**: Enforces `WRITE_SETTINGS` or `WRITE_SECURE_SETTINGS`.

## Detailed Functionality

### Pointer Speed
- `get/setPointerSpeed`: Mouse pointer speed (-7 to 7).
- `get/setTouchpadPointerSpeed`: Separated touchpad speed.

### Accessibility Features
- `Bounce Keys`: Threshold setup.
- `Slow Keys`: Threshold setup.
- `Sticky Keys`: Toggle.
- `Mouse Keys`: Toggle.

### Mouse Options
- Scrolling speed, acceleration, reverse scrolling, primary button swap.

### Touchpad Options
- Natural scrolling, tap-to-click, tap-dragging, right-click zone.
- Visualizer, system gestures (3/4 finger).

### Input Features
- `MaximumObscuringOpacityForTouch`: Security setting for overlays.
- `StylusEverUsed`: Tracking metric.

## Data Model
- Constants for default values and min/max ranges.

## Java-to-C++ Translation Guide
- **Settings Access**: C++ needs access to `SettingsProvider` (via ContentProviderClient or similar system service call). This is often easier to keep in Java or JNI.
- **Flags**: C++ Aconfig flags.

## Test Cases & Validation
- Verify range checks (e.g., speed between -7 and 7).
- Verify correct Settings keys are modified.

## Implementation Risks
- Feature flag divergence between Java and C++ if not synchronized.
