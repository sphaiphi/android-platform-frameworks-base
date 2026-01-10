# InputDeviceVibrator - Reverse Engineering Documentation

## Executive Summary
`InputDeviceVibrator` implements the `android.os.Vibrator` abstract class, providing vibration control for specific input devices by delegating to `InputManagerGlobal`.

## Architecture Overview
- **Inheritance**: Extends `android.os.Vibrator`.
- **Target**: Binds to a specific `deviceId` and `vibratorId`.
- **Token**: Uses a `Binder` token to identify vibration sessions.

## Detailed Functionality

### Capability Reporting
- **hasVibrator()**: Always true (instance wouldn't exist otherwise).
- **hasAmplitudeControl()**: Checks `VibratorInfo`.

### Vibration Control
- **vibrate()**: Calls `mGlobal.vibrate()`.
- **cancel()**: Calls `mGlobal.cancelVibrate()`.

### Listener Management
- **addVibratorStateListener()**: Registers a listener via `mGlobal.registerVibratorStateListener`. Uses a delegate to handle threading/executor.
- **removeVibratorStateListener()**: Unregisters.

## Data Model
- `mDeviceId`: int.
- `mVibratorInfo`: `VibratorInfo` (capabilities).
- `mToken`: `Binder` (Identity token for cancellation).

## API Reference
- Standard `Vibrator` API.

## Java-to-C++ Translation Guide
- **Binder Token**: Use `sp<BBinder>` for the token.
- **Async Callbacks**: Implement listener logic using standard C++ callbacks/futures.

## Implementation Risks
- None. Straightforward proxy pattern.
