# Vibrator - Reverse Engineering Documentation

## Executive Summary
`Vibrator` is an abstract class that provides access to the vibration hardware on a device. It allows applications to play simple "one-shot" vibrations, complex patterns, or pre-defined haptic effects. It also supports querying the hardware's capabilities, such as amplitude and frequency control.

## Architecture Overview
- **Service Type**: System-level service retrieved via `Context.VIBRATOR_SERVICE`.
- **Hierarchy**: An abstract base class. The actual implementation is typically `SystemVibrator`, which communicates with `VibratorManagerService`.
- **HAL Interaction**: Eventually talks to the Vibrator HAL (`android.hardware.vibrator`).
- **Control**: Supports both time-based durations and effect-based vibrations (`VibrationEffect`).

## Detailed Functionality

### Vibration Execution
**Purpose**: To provide tactile feedback to the user.
**Methods**:
- `vibrate(long ms)`: Legacy simple vibration.
- `vibrate(VibrationEffect)`: Modern API for playing waveforms or primitives.
- `cancel()`: Immediately stop any ongoing vibration.

### Capability Discovery
**Purpose**: To tailor haptic feedback based on hardware sophistication.
**Capabilities**:
- `hasAmplitudeControl()`: Support for varying the strength of the vibration.
- `hasFrequencyControl()`: Support for varying the pitch/frequency.
- `areEffectsSupported(int...)`: Check for built-in effects like `EFFECT_CLICK` or `EFFECT_TICK`.

### Synchronization
**Java-Specific Notes**: Vibrations are associated with a `VibrationAttributes` object, which defines the usage (e.g., `USAGE_ALARM`, `USAGE_NOTIFICATION`) and helps the system prioritize concurrent vibration requests.

## Data Model

### Intensity Levels
- `VIBRATION_INTENSITY_LOW` (1)
- `VIBRATION_INTENSITY_MEDIUM` (2)
- `VIBRATION_INTENSITY_HIGH` (3)

### Effect Support
- `VIBRATION_EFFECT_SUPPORT_YES` (1)
- `VIBRATION_EFFECT_SUPPORT_NO` (2)

## API Reference

### Public Methods
- `boolean hasVibrator()`: Hardware check.
- `void vibrate(VibrationEffect effect)`: Primary entry point.
- `int[] areEffectsSupported(int... effectIds)`: Compatibility check.
- `float getResonantFrequency()`: Physical property of the motor.

## Java-to-C++ Translation Guide

### Abstract Interface
- **Java**: `public abstract class Vibrator`.
- **C++**: Use a C++ abstract class or interface (`class IVibrator`).

### Effect Marshalling
- **Java**: `VibrationEffect` is a complex object.
- **C++**: The C++ implementation must serialize `VibrationEffect` into the format expected by the Vibrator HAL (typically a set of `CompositePrimitive` structs or a simple duration).

### Thread Safety
- **Java**: Handled by the system service.
- **C++**: Vibration requests should be dispatched to a background thread to avoid blocking the caller, especially for long patterns or those requiring complex timing.

## Test Cases & Validation
1. **Hardware Presence**: Verify `hasVibrator()` returns true on a phone and false on most tablets/emulators.
2. **Cancellation**: Start a 10-second vibration and call `cancel()` after 1 second; verify the motor stops immediately.
3. **Effect Fallback**: Request an unsupported effect and verify that the system plays a fallback (if configured) or returns the correct support status.

## Implementation Risks
- **Concurrency**: Multiple apps might try to vibrate at once. The implementation must use the `VibrationAttributes` to decide which one "wins" based on system policy.
- **Battery Life**: Heavy use of the vibrator is power-intensive. The C++ implementation should enforce system-wide limits on vibration duration.