# InputManagerGlobal - Reverse Engineering Documentation

## Executive Summary
`InputManagerGlobal` is a singleton that manages the persistent connection to the `IInputManager` system service and handles process-wide state like registered listeners (device, battery, tablet mode, etc.).

## Architecture Overview
- **Singleton**: Accessible via `getInstance()`.
- **Binder Cache**: Holds `IInputManager` stub.
- **Listener Multiplexing**: Registers one AIDL listener with the system server per type (e.g., `IInputDevicesChangedListener`) and dispatches events to multiple local listeners in the application process.

## Detailed Functionality

### Listener Management
- **Input Device Listeners**:
  - Maintains `SparseArray<InputDevice> mInputDevices`.
  - Implements `IInputDevicesChangedListener`.
  - Dispatches `onInputDeviceAdded/Removed/Changed` to local `InputDeviceListenerDelegate`s on their respective threads.
- **Tablet Mode**:
  - Implements `ITabletModeChangedListener`.
  - Dispatches to `OnTabletModeChangedListener`.
- **Battery**:
  - Implements `IInputDeviceBatteryListener`.
  - Maps `deviceId` to list of listeners.
- **Keyboard Backlight**:
  - Implements `IKeyboardBacklightListener`.
- **Sensors**:
  - Manages `InputDeviceSensorManager`.

### Device Cache
- `getInputDevice(id)` checks local cache. If missing/invalidated, fetches from server and caches it.
- Updates cache on `onInputDevicesChanged` callback.

### Service Delegation
- Most public methods just forward calls to `mIm` (IInputManager) and handle `RemoteException`.

## Data Model
- `SparseArray<InputDevice> mInputDevices`
- `ArrayList<InputDeviceListenerDelegate> mInputDeviceListeners`
- `SparseArray<RegisteredBatteryListeners> mBatteryListeners`

## Java-to-C++ Translation Guide
- **Global State**: Global static instance.
- **Callback Dispatch**: C++ needs a mechanism to dispatch callbacks to specific threads (Loopers).
- **Caching**: Mirror the device caching strategy to avoid excessive Binder calls.

## Implementation Risks
- **Deadlock**: Multiple locks (`mInputDeviceListeners`, `mBatteryListenersLock`, etc.). Care must be taken to avoid calling out to foreign code while holding locks.
- **Binder limits**: Though multiplexing reduces listener count on server, the number of events can be high.
