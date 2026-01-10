# DeviceStateManager - Reverse Engineering Documentation

## Executive Summary
`DeviceStateManager` is the public API surface (System Service) for interacting with device states. It provides methods to request state changes, listen for updates, and manage base state overrides. It delegates the heavy lifting of IPC communication to `DeviceStateManagerGlobal`.

## Architecture Overview
- **Pattern**: Manager / Facade
- **Scope**: System Service (`Context.DEVICE_STATE_SERVICE`)
- **Dependencies**: `DeviceStateManagerGlobal` (Singleton).

## Detailed Functionality

### State Management
- **Request State**: Allows apps to request a specific state (e.g., "Rear Display Mode").
- **Cancel Request**: Cancels the current active request.
- **Base State Override**: (Testing only) Forces the system to believe the physical state has changed.

### Callbacks
- **`DeviceStateCallback`**: Interface for clients to receive `onSupportedStatesChanged` and `onDeviceStateChanged`.
- **`FoldStateListener`**: A specific utility helper that translates device states into a boolean "folded" state based on configuration arrays (`config_foldedDeviceStates`) or properties.

## API Reference
- `requestState(...)`: Delegates to Global.
- `cancelStateRequest()`: Delegates to Global.
- `registerCallback(...)`: Delegates to Global.
- `getSupportedDeviceStates()`: Returns `List<DeviceState>`.

## Java-to-C++ Translation Guide
- This class is primarily a Java-side API wrapper.
- **In C++ context**: This likely corresponds to a Client API class or is bypassed if interacting directly with the Binder interface.
- **FoldStateListener Logic**: This logic is client-side. If C++ clients need "isFolded" logic, they must implement equivalent checking against `PROPERTY_FOLDABLE_DISPLAY_CONFIGURATION_OUTER_PRIMARY` or a config array.

## Implementation Risks
- **Permission Checks**: Java uses `@RequiresPermission`. C++ service implementation must enforce `android.permission.CONTROL_DEVICE_STATE`.
