# CompanionDeviceManager - Reverse Engineering Documentation

## Executive Summary
`CompanionDeviceManager` (CDM) is the primary system API for managing companion devices. It allows apps to request device discovery, establish associations without broad runtime permissions, monitor device presence, and transfer system data (like call metadata or permissions) through bidirectional streams.

## Architecture Overview
CDM follows the standard Android System Service pattern:
- **Proxy**: `CompanionDeviceManager` (Client-side API).
- **Stub**: `ICompanionDeviceManager` (Binder interface).
- **Service**: `CompanionDeviceManagerService` (System server implementation).

It integrates with the Bluetooth and Wi-Fi stacks and uses a bipartite model involving a Host (app) and a Provider (device).

## Detailed Functionality

### Association Management
**Purpose**: Establishing a link between an app and a device.
**Algorithm**:
1. App calls `associate(AssociationRequest, Executor, Callback)`.
2. CDM Service checks permissions and profile requirements.
3. If user confirmation is needed, CDM returns an `IntentSender`.
4. App launches the UI encapsulated in the `IntentSender`.
5. Upon user approval, CDM Service records the association and notifies the app via `onAssociationCreated`.

### Device Presence Monitoring
**Purpose**: Notifying apps when a device comes in or out of range.
**Mechanism**:
- Apps call `startObservingDevicePresence`.
- For BLE: Triggers background scanning.
- For Classic Bluetooth: Triggers on connection/disconnection events.
- Notifications are delivered to a registered `CompanionDeviceService`.

### System Data Transport
**Purpose**: Efficiently syncing data between devices.
**Mechanism**:
- CDM uses a `Transport` mechanism (internally using `socketpair` or pipes).
- Apps attach streams via `attachSystemDataTransport(int, InputStream, OutputStream)`.
- This allows the system to shuttle data payloads without Binder traffic contention for large transfers.

### Permission and Call Metadata Sync
**Purpose**: Specific data types like call muting/ending or permission states can be synced across the association.
**Flags**: `FLAG_CALL_METADATA`.

## Data Model
- `AssociationInfo`: Record of an established link.
- `AssociationRequest`: Parameters for discovery.
- `Result Codes`: `RESULT_OK`, `RESULT_CANCELED`, `RESULT_USER_REJECTED`, `RESULT_DISCOVERY_TIMEOUT`, `RESULT_INTERNAL_ERROR`, `RESULT_SECURITY_ERROR`.

## API Reference
- `getMyAssociations()`: Returns `List<AssociationInfo>`.
- `disassociate(int associationId)`: Removes an association.
- `requestNotificationAccess(ComponentName)`: Specific helper for wearable notification sync.
- `sendMessage(int, byte[], int[])`: Sends raw bytes to connected transports.

## Java-to-C++ Translation Guide
- **Binder**: Use NDK Binder or libbinder for C++ IPC.
- **Streams**: Map `InputStream`/`OutputStream` to native file descriptors or socket-based streams.
- **Transports**: The internal `Transport` class uses threads to shuttle data; implement using `std::thread` or `std::jthread`.
- **Callbacks**: Use AIDL-generated listeners (`IOnAssociationsChangedListener`, etc.).

## Implementation Risks
- **Thread Safety**: Transport management and listener proxies require strict synchronization (uses `synchronized` blocks in Java).
- **Resource Lifecycle**: Transports must be properly detached and streams closed to prevent leaks.
- **Background Constraints**: CDM influences the Low-Memory Killer (LMK) priority by binding to services; C++ reimplementation must ensure the system server is notified of these priority changes.
