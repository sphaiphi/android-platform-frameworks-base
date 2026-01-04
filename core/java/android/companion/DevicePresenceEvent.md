# DevicePresenceEvent - Reverse Engineering Documentation

## Executive Summary
`DevicePresenceEvent` is a data class representing a change in the physical presence or connection status of a companion device. It is used to notify applications via the `CompanionDeviceService` when devices appear or disappear from range.

## Architecture Overview
This class implements `Parcelable` and is used as the payload for the `onDevicePresenceEvent` callback. It categorizes events into BLE proximity, Bluetooth connection, and self-managed reporting.

## Detailed Functionality

### Event Types
The class defines integer constants for various states:
- `EVENT_BLE_APPEARED` (0): Device entered BLE range.
- `EVENT_BLE_DISAPPEARED` (1): Device left BLE range.
- `EVENT_BT_CONNECTED` (2): Classic Bluetooth connection established.
- `EVENT_BT_DISCONNECTED` (3): Classic Bluetooth connection lost.
- `EVENT_SELF_MANAGED_APPEARED` (4): App-managed device reported as present.
- `EVENT_SELF_MANAGED_DISAPPEARED` (5): App-managed device reported as gone.

### Identification
Events can be tied to either:
1. **Association ID**: The unique ID of an established CDM association.
2. **UUID**: A `ParcelUuid` for devices being monitored by service UUID rather than established association.

## Data Model
- `mAssociationId`: int - ID of the association, or `-1` if not applicable.
- `mEvent`: int - One of the `EVENT_*` constants.
- `mUuid`: `ParcelUuid` - Target UUID for observation.

## API Reference
- `getAssociationId()`: Returns the association link.
- `getEvent()`: Returns the presence state change.
- `getUuid()`: Returns the identifying UUID.

## Java-to-C++ Translation Guide
- **Event Enum**: Use `enum class PresenceEvent`.
- **Union Identification**: Since an event is either for an Association or a UUID, consider using `std::variant<int, ParcelUuid>` for the target identifier in C++.
- **Serialization**: Standard AIDL parcelable. Note the use of `PARCEL_UUID_NULL` (0) and `PARCEL_UUID_NOT_NULL` (1) flags during writing to handle nullability.

## Implementation Risks
- **Race Conditions**: Presence events can fire rapidly (e.g., at the edge of BLE range). C++ listeners must handle high-frequency updates and potential stale events.
- **Null Safety**: Always check the UUID null flag during reconstruction.
