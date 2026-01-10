# VibratorManager - Reverse Engineering Documentation

## Executive Summary
`VibratorManager` provides access to all vibrators on a device, which is especially useful for devices with multiple haptic actuators (e.g., left and right side vibrators). It allows for synchronized vibrations across multiple motors and provides a gateway to the default system vibrator.

## Architecture Overview
- **Service Type**: System-level service retrieved via `Context.VIBRATOR_MANAGER_SERVICE`.
- **Relationship**: Acts as a manager for multiple `Vibrator` instances.
- **Backend Interaction**: Communicates with the `IVibratorManagerService` binder.
- **Coordination**: Supports `CombinedVibration` for multi-vibrator effects.

## Detailed Functionality

### Vibrator Enumeration
**Purpose**: To discover the device's haptic topology.
**Algorithm**:
1. Call `getVibratorIds()`.
2. Returns an `int[]` of all physical vibrator IDs.
3. Call `getVibrator(id)` to get a `Vibrator` instance for a specific motor.

### Synchronized Vibration
**Purpose**: To play patterns on multiple vibrators simultaneously.
**Algorithm**:
1. Create a `CombinedVibration` object (e.g., using `ParallelCombination`).
2. Call `vibrate(CombinedVibration)`.
3. The system service ensures all targeted motors start their respective effects at the same time.

### Default Vibrator
**Purpose**: To provide a convenient entry point for single-vibrator devices.
**Method**: `getDefaultVibrator()` returns the primary haptic motor.

## Data Model

### Identification
- `mPackageName`: Used for attribution and permission checking.

## API Reference

### Public Methods
- `int[] getVibratorIds()`: Discovery.
- `Vibrator getVibrator(int vibratorId)`: Targeted control.
- `Vibrator getDefaultVibrator()`: Primary control.
- `void vibrate(CombinedVibration effect)`: Multi-motor control.

## Java-to-C++ Translation Guide

### Multi-Motor Topology
- **Java**: `SparseArray` or similar mapping of IDs to `Vibrator` objects.
- **C++**: Use a `std::map<int32_t, std::unique_ptr<Vibrator>>` to manage the lifecycle of individual actuator proxies.

### IPC Layer
- **Java**: `IVibratorManagerService` binder.
- **C++**: Obtain the `vibrator_manager` service from `ServiceManager`. Use the native `IVibratorManagerService` interface.

## Test Cases & Validation
1. **Enumeration Accuracy**: On a device with stereo haptics, verify `getVibratorIds()` returns exactly two IDs.
2. **Synchronicity**: Trigger a parallel vibration on two motors and use a high-speed camera or oscilloscope to verify they start within a few milliseconds of each other.
3. **Default Mapping**: Ensure `getDefaultVibrator().getId()` matches the first ID in the list returned by `getVibratorIds()`.

## Implementation Risks
- **Hardware Variation**: Some devices report multiple vibrators but only one is physically present or accessible. The C++ implementation must handle empty or inconsistent ID lists from the HAL.
- **Resource Locking**: Synchronizing multiple motors requires careful timing in the HAL layer to avoid jitter.