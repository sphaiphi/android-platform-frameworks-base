# BrightnessInfo - Reverse Engineering Documentation

## Executive Summary
`BrightnessInfo` is a simple data container (Parcelable) that holds current status information about the display's brightness, including HBM (High Brightness Mode) status, thermal throttling reasons, and min/max limits.

## Architecture Overview
- **Type**: Immutable Data Object / Parcelable
- **Package**: `android.hardware.display`

## Data Model
- **Brightness Values**: `brightness`, `adjustedBrightness`, `brightnessMinimum`, `brightnessMaximum`.
- **HBM**: `highBrightnessMode` (Off, Sunlight, HDR), `highBrightnessTransitionPoint` (Threshold where HBM kicks in).
- **Throttling**: `brightnessMaxReason` (None, Thermal, Power IC, Wear Bedtime).
- **Override**: `isBrightnessOverrideByWindow`.

## Java-to-C++ Translation Guide
- Simple struct mapping.
- **Enums**: Map `HIGH_BRIGHTNESS_MODE_*` and `BRIGHTNESS_MAX_REASON_*` to C++ enums or constants.

## API Reference
- `hbmToString(int)`: Utility for logging.
- `briMaxReasonToString(int)`: Utility for logging.
