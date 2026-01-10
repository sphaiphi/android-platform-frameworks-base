# AssociationInfo - Reverse Engineering Documentation

## Executive Summary
`AssociationInfo` is a final class representing an established "association" between an Android application and a companion device. It acts as a data record containing metadata about the relationship, such as device IDs, MAC addresses, display names, and various state flags (e.g., revoked, pending).

## Architecture Overview
This class is a `Parcelable` data object. It is used to communicate association details between the `CompanionDeviceManagerService` and client applications. It includes a `Builder` for construction, primarily for system use or testing.

## Detailed Functionality

### Core Attributes
- **Identity**: Unique ID (`mId`), User ID (`mUserId`), and Package Name (`mPackageName`).
- **Device Identifiers**: MAC Address (`mDeviceMacAddress`) and a logic-specific `DeviceId` (`mDeviceId`).
- **UI Metadata**: Display Name (`mDisplayName`), Device Profile (e.g., "watch"), and an optional `Icon`.
- **State Management**:
    - `mSelfManaged`: Boolean indicating if the app handles the connection itself.
    - `mRevoked`: Indicates the association is being removed.
    - `mPending`: Indicates the association is waiting for the app to be installed (backup/restore scenario).
    - `mNotifyOnDeviceNearby`: Flag for binding triggers.
- **Timestamps**: `mTimeApprovedMs` and `mLastTimeConnectedMs`.

### Logic: Icon Comparison
**Purpose**: `isSameIcon` compares two icons by their bitmaps.
**Java-Specific Notes**: Uses `Icon.getBitmap().sameAs(other.getBitmap())`. This assumes icons have been normalized to bitmaps before storage/comparison.

### Logic: MAC Address Checks
**Purpose**: `isLinkedTo(String addr)` validates if the association matches a specific hardware address.
**Algorithm**: Parses the string to `MacAddress` and compares. Returns false for self-managed associations.

## Data Model
| Field | Type | Description |
|-------|------|-------------|
| mId | int | Unique ID (must be > 0). |
| mUserId | int | ID of the user owner. |
| mPackageName | String | Package name of the app. |
| mDeviceMacAddress | MacAddress | Hardware address. |
| mDisplayName | CharSequence | User-visible name. |
| mDeviceProfile | String | Profile string (e.g. COMPANION_DEVICE_WATCH). |
| mAssociatedDevice| AssociatedDevice | Container for the underlying device object (transient-ish). |
| mSystemDataSyncFlags| int | Flags for syncing system data. |

## API Reference
- `isActive()`: Returns `!mRevoked && !mPending`.
- `shouldBindWhenPresent()`: Returns `mNotifyOnDeviceNearby || mSelfManaged`.
- `toShortString()`: Provides a compact log-friendly representation.

## Java-to-C++ Translation Guide
- **Immutable State**: This class is immutable in Java. Use `const` members or a private implementation with public getters in C++.
- **Types**: 
    - `MacAddress` -> Native MacAddress representation.
    - `CharSequence` -> `std::u16string` or `std::string`.
    - `Icon` -> Native Icon/Drawable wrapper.
- **Serialization**: Standard AIDL parcelable implementation. Note that `mAssociatedDevice` uses `writeTypedObject`.

## Implementation Risks
- **Nullability**: Many fields are `@Nullable`. C++ implementation must use `std::optional` or pointers with clear ownership to avoid null dereferences.
- **Icon Comparison**: Comparing bitmaps is expensive. Consider if a hash or identifier comparison is sufficient in the C++ layer.
