# StorageStats - Reverse Engineering Documentation

## Executive Summary
`StorageStats` provides detailed storage breakdown for a UID or Package. It distinguishes between code, data, cache, and various ART (Android Runtime) artifacts like dexopt code and profiles.

## Architecture Overview
- **Implements**: `Parcelable`.
- **Integration**: Can lazily fetch ART-specific stats via `IStorageStatsManager` if requested.

## Detailed Functionality

### Fields
- **Identity**: `packageName`, `userHandle`, `uid`.
- **Standard Storage**: `codeBytes`, `dataBytes`, `cacheBytes`.
- **External**: `externalCacheBytes`.
- **ART Artifacts** (Optional/Flagged):
    - `dexoptBytes`: Optimized code.
    - `curProfBytes`, `refProfBytes`: Profiles for PGO.
    - `apkBytes`, `libBytes`, `dmBytes`.

### ART Stats Fetching (`getArtManagedStats`)
**Logic**:
- Checks if `Flags.getAppArtManagedBytes()` is enabled and if `artStatsFetched` is false.
- If true, connects to `storagestats` service (`IStorageStatsManager`).
- Calls `queryArtManagedStats` to populate `dexoptBytes`, `curProfBytes`, `refProfBytes`.
- Sets `artStatsFetched = true`.

### Parceling
- Writes/Reads identity fields and the 6 main long values + ART values.

## Data Model

| Field | Type | Note |
| :--- | :--- | :--- |
| `packageName` | String | |
| `userHandle` | int | |
| `uid` | int | |
| `codeBytes` | long | |
| `dataBytes` | long | |
| `cacheBytes` | long | |
| `externalCacheBytes` | long | |
| `dexoptBytes` | long | |
| `refProfBytes` | long | |
| `curProfBytes` | long | |
| `apkBytes` | long | |
| `libBytes` | long | |
| `dmBytes` | long | |

## API Reference
- Getters for totals (`getAppBytes`, `getDataBytes`, etc.).
- `getAppBytesByDataType(int type)`: Granular access.

## Java-to-C++ Translation Guide
- **Lazy Loading**: The C++ implementation must consider if it needs to support the lazy IPC fetch to `storagestats`. If this object is being passed *from* system *to* client, the fetch might have happened or be unnecessary. If the C++ code is the *client*, it might need to replicate the `getArtManagedStats` logic if it consumes these fields.
- **Service Manager**: `ServiceManager.getService("storagestats")` in C++ via `defaultServiceManager()`.

## Implementation Risks
- **Dependency**: Depends on `IStorageStatsManager`.
- **Flagging**: Behavior changes based on feature flags.
