# InputDeviceVibratorManager - Reverse Engineering Documentation

## Executive Summary
`InputDeviceVibratorManager` implements `VibratorManager` to manage multiple vibrators on a single input device (e.g., game controllers with left/right rumble).

## Architecture Overview
- **Inheritance**: Extends `android.os.VibratorManager`.
- **Listener**: Implements `InputManager.InputDeviceListener` to handle device changes (re-initializing vibrators).

## Detailed Functionality

### Initialization
- Fetches all vibrator IDs for the device via `mGlobal.getVibratorIds(mDeviceId)`.
- Creates `InputDeviceVibrator` instances for each ID.

### Vibrator Access
- **getVibratorIds()**: Returns list of IDs.
- **getVibrator(int id)**: Returns specific vibrator instance.
- **getDefaultVibrator()**: Returns the vibrator with ID 0.

### Device Lifecycle
- **onInputDeviceChanged**: Refreshes the list of vibrators if the device descriptor changed.
- **onInputDeviceRemoved**: Clears local vibrator cache.

## Data Model
- `mVibrators`: `SparseArray<Vibrator>`.
- `mDeviceId`: int.

## Java-to-C++ Translation Guide
- **SparseArray**: `std::map<int, std::shared_ptr<Vibrator>>`.
- **Locking**: `synchronized` blocks map to `std::mutex`.

## Implementation Risks
- Handling dynamic addition/removal of vibrators if the hardware capability changes (rare).
