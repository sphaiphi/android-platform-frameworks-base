# CompanionDeviceService - Reverse Engineering Documentation

## Executive Summary
`CompanionDeviceService` is an abstract base class that companion applications must extend to receive lifecycle events and presence updates from the system. It enables apps to respond to devices appearing or disappearing in range and facilitates the attachment of bidirectional communication streams for system data transport.

## Architecture Overview
This is a standard Android `Service` that acts as a callback target for the `CompanionDeviceManagerService`.
- **System-to-App**: The system binds to this service when an associated device is detected.
- **App-to-System**: The app uses this service context to attach/detach data transports.

## Detailed Functionality

### Binding Lifecycle
**Purpose**: Elevates the app process priority to prevent it from being killed by the Low-Memory Killer (LMK) while interacting with a device.
**Mechanism**:
- System calls `onBind` with `SERVICE_INTERFACE` ("android.companion.CompanionDeviceService").
- Returns an internal Binder stub (`ICompanionDeviceService.Stub`).

### Presence Callbacks
**Purpose**: Notify the app of device vicinity changes.
- `onDeviceAppeared(AssociationInfo)`: Called when a device is nearby or connected.
- `onDeviceDisappeared(AssociationInfo)`: Called when a device is out of range or disconnected.
- `onDevicePresenceEvent(DevicePresenceEvent)`: Modern unified callback for more granular events (BLE appear, BT connect, etc.).

### Stream Attachment
**Purpose**: Helper methods to delegate transport management to `CompanionDeviceManager`.
- `attachSystemDataTransport(int associationId, InputStream in, OutputStream out)`: Connects app-provided streams to the system's sync logic.

## Logic: Primary Service Selection
If an app declares multiple `CompanionDeviceService` implementations, the system uses the `android.companion.PROPERTY_PRIMARY_COMPANION_DEVICE_SERVICE` property to determine which one receives the presence callbacks.

## Data Model
- `Stub`: Internal class implementing `ICompanionDeviceService.aidl` to receive IPC calls.
- `mMainHandler`: Used to post callbacks to the main UI thread.

## API Reference
- `onDeviceAppeared(String address)`: **Deprecated**.
- `onDeviceAppeared(AssociationInfo)`: **Deprecated**.
- `onDevicePresenceEvent(DevicePresenceEvent)`: The recommended callback for all presence changes.

## Java-to-C++ Translation Guide
- **Service Model**: In C++, this would be a client-side listener or a dedicated daemon component.
- **Threading**: Callbacks in Java are posted to the main thread. C++ implementation should allow specifying a `Looper` or `Executor`.
- **Binder**: Re-implement `ICompanionDeviceService` stub logic using C++ Binder.

## Implementation Risks
- **Callback Latency**: Since updates are posted via `mMainHandler`, a busy UI thread can delay presence notifications. C++ implementation should consider a dedicated callback thread.
- **Unbinding Logic**: The service is unbound when all associated devices are gone. Ensure RAII cleanup of any resources held by the service implementation.
