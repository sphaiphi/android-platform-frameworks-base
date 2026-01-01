# PowerManager - Reverse Engineering Documentation

## Executive Summary
`PowerManager` is a critical system service that controls the device's power state, including the display (backlight), CPU (wake locks), and thermal management. it provides APIs for keeping the device awake to perform background tasks and for discovering the current power and thermal constraints.

## Architecture Overview
- **Service Type**: System-level service retrieved via `Context.POWER_SERVICE`.
- **Backend Interaction**: Communicates with the `IPowerManager` (native `PowerManagerService`) and `IThermalService`.
- **Core Components**:
    - **WakeLocks**: Mechanisms to prevent the CPU or screen from going into a low-power state.
    - **User Activity**: Tracks inputs to manage the screen timeout timer.
    - **Thermal Management**: Monitors device temperature and notifies apps of throttling.

## Detailed Functionality

### WakeLock Management
**Purpose**: To ensure the device remains operational during critical tasks.
**Types**:
- `PARTIAL_WAKE_LOCK`: Keeps CPU running; screen can turn off.
- `PROXIMITY_SCREEN_OFF_WAKE_LOCK`: Turns screen off when something is near the sensor (handset mode).
- `ACQUIRE_CAUSES_WAKEUP`: Forces the screen to turn on immediately upon acquisition.

### Device States
- **Interactive**: The device is awake and ready for user interaction.
- **Sleep/Doze**: Low-power states where most components are suspended.
- **Shutdown/Reboot**: Methods to trigger system power cycles.

### Thermal Throttling
**Purpose**: To prevent hardware damage due to overheating.
**Algorithm**:
1. `ThermalService` monitors internal sensors.
2. If temperature crosses thresholds, `PowerManager` notifies registered `OnThermalStatusChangedListener`s.
3. Apps are expected to reduce their workload (e.g., lower video resolution, disable GPS).

## Data Model

### WakeLock Levels
- `PARTIAL_WAKE_LOCK` (0x1)
- `SCREEN_DIM_WAKE_LOCK` (0x6)
- `SCREEN_BRIGHT_WAKE_LOCK` (0xA)
- `FULL_WAKE_LOCK` (0x1A)

### Wake Reasons
- `POWER_BUTTON`, `PLUGGED_IN`, `GESTURE`, `BIOMETRIC`.

## API Reference

### Public Methods
- `WakeLock newWakeLock(int levelAndFlags, String tag)`: Create a lock.
- `boolean isInteractive()`: Check if device is awake.
- `void reboot(String reason)`: Trigger a reboot.
- `void addThermalStatusListener(OnThermalStatusChangedListener listener)`: Monitor heat.

## Java-to-C++ Translation Guide

### WakeLock Implementation
- **Java**: `WakeLock` class with `acquire()` and `release()`.
- **C++**: Use RAII-based `android::os::PowerManager::WakeLock` or similar. Ensure `release()` is called in the destructor.

### Service IPC
- **Java**: `IPowerManager` binder.
- **C++**: Obtain the `power` service from `android::defaultServiceManager()`. Use the native `IPowerManager` interface.

### Thermal Status
- **Java**: Callback-based.
- **C++**: Use `IThermalService` and implement `BnThermalStatusListener`.

## Test Cases & Validation
1. **CPU Persistence**: Acquire a `PARTIAL_WAKE_LOCK` and verify that the CPU does not suspend even if the screen is off (check `/sys/power/state` or logcat).
2. **Thermal Notification**: Simulate a high-temperature event via `dumpsys battery set temp` and verify the listener receives the `THERMAL_STATUS_CRITICAL` status.
3. **Screen Timeout**: Trigger `userActivity()` and verify that the screen timeout timer is reset.

## Implementation Risks
- **Battery Drain**: Leaked wake locks are a major source of battery drain. The implementation must ensure all locks are tagged and potentially timed out by the system.
- **Deadlocks**: Power state changes often involve multiple services (Display, WindowManager, HAL). Careful lock ordering is required in the C++ implementation.
