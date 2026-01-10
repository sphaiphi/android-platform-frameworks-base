# NanoAppState - Reverse Engineering Documentation

## Executive Summary
`NanoAppState` describes the runtime state of a nanoapp, including its ID, version, enabled status, permissions, and published RPC services. It is the modern replacement for `NanoAppInstanceInfo`.

## Architecture Overview
- **Pattern**: State Object / DTO.
- **Inheritance**: Implements `android.os.Parcelable`.

## Data Model
| Field | Type | Description |
|---|---|---|
| `mNanoAppId` | `long` | App ID. |
| `mNanoAppVersion` | `int` | Version. |
| `mIsEnabled` | `boolean` | Running state. |
| `mNanoAppPermissions` | `List<String>` | Required Android permissions. |
| `mNanoAppRpcServiceList` | `List<NanoAppRpcService>` | Published services. |

## Java-to-C++ Translation Guide
- **Data Structure**: Struct with `std::vector` for lists.

## Questions for C++ Team
- None.
