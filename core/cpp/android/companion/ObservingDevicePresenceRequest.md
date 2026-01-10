# ObservingDevicePresenceRequest - Reverse Engineering Documentation

## Executive Summary
`ObservingDevicePresenceRequest` encapsulates the parameters for an application's request to start monitoring the physical presence of a companion device. It supports monitoring based on either an existing association ID or a specific Bluetooth service UUID.

## Architecture Overview
This class implements `Parcelable` and uses a `Builder` pattern. It enforces a strict "choose one" policy between Association-based and UUID-based monitoring.

## Detailed Functionality

### Monitoring Modes
**Purpose**: To allow apps to listen for device range events.
1. **Association ID Mode**:
    - Requires a previously established CDM association.
    - Triggers events based on specific MAC/Identity of that association.
2. **UUID Mode**:
    - Does not require a prior association.
    - Monitors for any device advertising the specified `ParcelUuid`.
    - Requires specific permissions: `REQUEST_OBSERVE_DEVICE_UUID_PRESENCE`, `BLUETOOTH_CONNECT`, `BLUETOOTH_SCAN`.
    - Primarily intended for `DEVICE_PROFILE_AUTOMOTIVE_PROJECTION` profiles.

### Builder Validation
**Algorithm**:
The `build()` method performs internal consistency checks:
- Throws `IllegalStateException` if both `mUuid` and `mAssociationId` are set.
- Throws `IllegalStateException` if neither is set.

## Data Model
- `mAssociationId`: int - The target association ID.
- `mUuid`: `ParcelUuid` - The target service UUID.

## API Reference
- `getAssociationId()`: Returns the target ID or `NO_ASSOCIATION` (-1).
- `getUuid()`: Returns the target UUID or null.

## Java-to-C++ Translation Guide
- **Pattern**: Replicate the `Builder` pattern with the validation logic in the `build()` method.
- **Strong Types**: Use `std::optional<ParcelUuid>`.
- **Constraint Enforcement**: Use a `std::variant<int, ParcelUuid>` internally to make the mutually exclusive nature of the fields representable in the type system.

## Implementation Risks
- **Permission Mapping**: UUID observation requires significant platform permissions. C++ implementations in the system server must strictly verify these before honoring the request.
- **Lifecycle**: Requests should be tracked per calling UID to ensure they are cleaned up if the app process dies or the service is unbound.
