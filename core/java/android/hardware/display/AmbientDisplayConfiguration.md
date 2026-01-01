# AmbientDisplayConfiguration - Reverse Engineering Documentation

## Executive Summary
`AmbientDisplayConfiguration` is a utility class that acts as a facade for reading ambient display (Doze/Always-on Display) settings. It encapsulates the logic for checking system properties, resources (`config.xml`), and `Settings.Secure` values to determine if various "doze" features are enabled for a specific user.

## Architecture Overview
- **Type**: Configuration Reader / Helper
- **Package**: `android.hardware.display`
- **Dependencies**: `Context`, `Settings.Secure`, `SystemProperties`.

## Detailed Functionality

### Core Logic: Availability vs. Enabled
The class strictly separates "Available" (Hardware/Config support) from "Enabled" (User setting).
- **Available**: Checked via `R.bool.config_*` or `R.string.config_*` (checking for non-empty sensor strings).
- **Enabled**: Checked via `Settings.Secure` (defaults often depend on config).

### Feature Flags
It checks for:
- **Pulse on Notification**: `DOZE_ENABLED` + availability.
- **Pickup Gesture**: `DOZE_PICK_UP_GESTURE` + availability.
- **Tap/Double Tap**: `DOZE_TAP_SCREEN_GESTURE` / `DOZE_DOUBLE_TAP_GESTURE`.
- **Always On**: `DOZE_ALWAYS_ON` + `accessibilityInversion` check + availability.
- **Wake Lock Screen**: `DOZE_WAKE_LOCK_SCREEN_GESTURE`.
- **Wake Display**: `DOZE_WAKE_DISPLAY_GESTURE`.
- **Quick Pickup**: `DOZE_QUICK_PICKUP_GESTURE`.
- **UDFPS Long Press**: Fingerprint sensor gesture.

### Settings Management
- `disableDozeSettings(int userId)`: Backs up current settings to memory and sets them to "0" (disabled). Used possibly for power saving or testing.
- `restoreDozeSettings(int userId)`: Restores from memory.

## API Reference
Many public boolean methods taking `int user`:
- `enabled(int user)`: Master switch check (if any feature is on).
- `alwaysOnEnabled(int user)`
- `pulseOnNotificationEnabled(int user)`
- `pickupGestureEnabled(int user)`
- ...

## Java-to-C++ Translation Guide
- **Context/Resources**: C++ layers (SurfaceFlinger/SystemServer) usually access build configs via `sysprop` or internal configuration classes. Accessing `Settings.Secure` requires `ContentProvider` calls via Binder (`IContentProvider`).
- **Use Case**: This class is likely used by SystemUI (Java) and Settings (Java). If native code needs this, it should probably query `DisplayManagerService` or `PowerManagerService` rather than re-implementing the logic, as accessing `Settings.Secure` from native is heavy.
- **If Re-implementation is needed**:
    - Mapping `R.bool.*` to build flags/props.
    - Mapping `Settings.Secure.*` to direct Settings Provider calls.

## Implementation Risks
- **Settings Observer**: This class *reads* settings but doesn't appear to listen for changes (no `ContentObserver`). It fetches fresh values on every call. C++ implementation should consider caching if called frequently.
