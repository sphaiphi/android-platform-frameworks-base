# InputManager - Reverse Engineering Documentation

## Executive Summary
`InputManager` is the central System Service wrapper for the Android Input System. It provides access to input devices, keyboard layouts, pointer icons, and allows for event injection and monitoring. It acts as the public API surface for `InputManagerService`.

## Architecture Overview
- **System Service**: Registered as `Context.INPUT_SERVICE`.
- **Proxy Pattern**: Most methods delegate to `InputManagerGlobal` (singleton) or directly to `IInputManager` (Binder).
- **Permissions**: Many methods require restricted permissions (e.g., `INJECT_EVENTS`, `MONITOR_INPUT`).

## Detailed Functionality

### Device Management
- **getInputDevice(id)**: Retrieves `InputDevice` info.
- **getInputDeviceIds()**: Lists all connected device IDs.
- **enable/disableInputDevice()**: Control device availability.
- **registerInputDeviceListener()**: Callback for device connect/disconnect.

### Keyboard Layouts
- **getKeyboardLayouts()**: Lists available layouts.
- **setCurrentKeyboardLayoutForInputDevice()**: Sets layout for a device.
- **KeyboardLayoutPreview**: Generates visual previews of layouts.

### Input Monitoring
- **monitorGestureInput()**: (Deprecated) Access raw input stream.
- **pilferPointers()**: Steal touch events from other windows (used by Spy Windows / System UI).

### Event Injection & Verification
- **injectInputEvent()**: Injects `InputEvent` (Key/Motion) into the system.
- **verifyInputEvent()**: Cryptographically verifies if an event came from the system.

### System Settings & States
- **Pointer Speed**: Get/Set mouse velocity.
- **Tablet Mode**: Query status.
- **Mic Mute**: Query status.
- **Battery**: Monitor input device battery levels.
- **Lights/Vibrators**: Access sub-managers for lights and haptics.

### Associations
- **Port Associations**: Map input ports to display ports.
- **UniqueId Associations**: Map input devices to displays by descriptor.

## Data Model
- Relies on `InputDevice`, `KeyboardLayout`, `InputEvent`, etc.

## Java-to-C++ Translation Guide
- **Binder Client**: This class essentially wraps the Binder client `IInputManager`. In C++, this would correspond to using `BpInputManager` or similar `AIDL` generated client code.
- **Singleton**: The Java side uses `InputManagerGlobal` to share the binder connection. C++ likely has a similar singleton mechanism or service retrieval via `ServiceManager`.

## Test Cases & Validation
- **Injection**: Inject a key event and verify a listener receives it.
- **Device Listener**: Connect a virtual device and verify `onInputDeviceAdded` is called.

## Implementation Risks
- **Security**: Strict permission checks on server side. Client must handle `SecurityException`.
- **Concurrency**: Listener callbacks come on specified Handlers/Loopers.
