# PermissionGroupUsage - Reverse Engineering Documentation

## Executive Summary
`PermissionGroupUsage` is a simple data class (Parcelable) representing the usage of a permission group by an application. It is used to pass usage information (e.g., for privacy indicators or dashboards) across IPC boundaries.

## Architecture Overview
- **Type**: Data Transfer Object (DTO) / Parcelable.
- **Auto-Generated**: Uses `@DataClass` for boilerplate generation (equals, hashCode, toString, Parcelable).

## Detailed Functionality
Stores details about a specific access event:
-   **Identity**: Package name, UID, Permission Group Name.
-   **Timing**: Last access time.
-   **State**: Active vs. recent access.
-   **Context**: Whether it was a phone call.
-   **Attribution**: Tags and labels for finer-grained attribution (e.g., "Location accessed by *Feature X*").
-   **Proxy**: Label of the proxy app if access was proxied.
-   **Device**: `persistentDeviceId` for multi-device support.

## Data Model
### `PermissionGroupUsage`
| Field | Type | Description |
| :--- | :--- | :--- |
| `mPackageName` | `String` | App accessing the permission. |
| `mUid` | `int` | UID of the app. |
| `mLastAccessTimeMillis` | `long` | Timestamp of access. |
| `mPermissionGroupName` | `String` | The group (e.g., MICROPHONE). |
| `mActive` | `boolean` | Is access currently active? |
| `mPhoneCall` | `boolean` | Is this a phone call? |
| `mAttributionTag` | `CharSequence` | Optional attribution tag. |
| `mAttributionLabel` | `CharSequence` | User-visible label for the tag. |
| `mProxyLabel` | `CharSequence` | Label of the proxy app (if any). |
| `mPersistentDeviceId` | `String` | Device ID where usage occurred. |

## Java-to-C++ Translation Guide
This is a standard Parcelable.
1.  **Struct**: Create a C++ struct with corresponding fields. Use `android::String16` for CharSequence/String.
2.  **Parceling**: Implement `readFromParcel` and `writeToParcel`.
    -   Note the bitmask usage in `writeToParcel` (`flg`) to handle booleans and nullables efficiently.
    -   **Important**: Replicate the bitmask logic exactly to maintain binary compatibility.

```cpp
// Bitmask logic example for C++
int flg = 0;
if (active) flg |= 0x10;
if (phoneCall) flg |= 0x20;
if (attributionTag) flg |= 0x40;
// ... write flg ...
```

## Implementation Risks
-   **Bitmask Sync**: The bitmask flags (0x10, 0x20, etc.) are implicitly defined in the generated code. Ensure these match exactly in the C++ implementation.
