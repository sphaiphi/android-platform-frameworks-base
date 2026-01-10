# ActivityRelaunchItem - Reverse Engineering Documentation

## Executive Summary
`ActivityRelaunchItem` is a transaction item that triggers the relaunch of an activity. This involves destroying the current activity instance and creating a new one, often due to configuration changes (like language or theme changes) that the activity cannot handle dynamically.

## Architecture Overview
- **Inheritance**: Extends `ActivityTransactionItem`.
- **Role**: Handles the complex process of preserving state, destroying, and recreating an activity.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `preExecute`
**Purpose**: Prepares the activity for relaunch.
**Algorithm**:
1. Check if the transaction is from the server (`!client.isExecutingLocalTransaction()`).
2. If from server, apply compatibility overrides to `mConfig`.
3. Call `client.prepareRelaunchActivity()` to get an `ActivityClientRecord`.
4. Store the returned record in `mActivityClientRecord`.
**Java-Specific Notes**:
- `ActivityClientRecord` is a handle to the activity's state in the app process.
- Logic depends on whether the transaction is local or remote.

### `execute`
**Purpose**: Executes the relaunch.
**Algorithm**:
1. If `mActivityClientRecord` is null, log debug message and return (cancelled).
2. Start tracing `activityRestart`.
3. Call `client.handleRelaunchActivity(mActivityClientRecord, pendingActions)`.
4. End tracing.

### `postExecute`
**Purpose**: Cleanup and reporting.
**Algorithm**:
1. Retrieve the `ActivityClientRecord`.
2. Call `client.reportRelaunch(r)` to notify the system.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mPendingResults` | `List<ResultInfo>` | Pending results to be delivered to the new instance. |
| `mPendingNewIntents` | `List<ReferrerIntent>` | New intents to be delivered. |
| `mConfig` | `MergedConfiguration` | Configuration for the new instance. |
| `mActivityWindowInfo` | `ActivityWindowInfo` | Window info for the new instance. |
| `mConfigChanges` | `int` | Bitmask of configuration changes. |
| `mPreserveWindow` | `boolean` | Whether to preserve the window during relaunch. |
| `mActivityClientRecord` | `ActivityClientRecord` | Transient state (not serialized), initialized in `preExecute`. |

### Serialization (Parcelable)
- **Flattening**:
  - Writes parent data.
  - `writeTypedList` for `mPendingResults`.
  - `writeTypedList` for `mPendingNewIntents`.
  - `writeTypedObject` for `mConfig` and `mActivityWindowInfo`.
  - `writeInt` for `mConfigChanges`.
  - `writeBoolean` for `mPreserveWindow`.
- **Unflattening**:
  - Reads parent data.
  - `createTypedArrayList` for lists.
  - Reads typed objects and primitives.
  - `mConfig` and `mActivityWindowInfo` are required non-null.

## API Reference

### `ActivityRelaunchItem(...)`
- **Constructor**: Initializes all fields. Creates defensive copies of lists and objects.

## Java-to-C++ Translation Guide

### Data Structures
- `List<ResultInfo>` -> `std::vector<ResultInfo>`.
- `List<ReferrerIntent>` -> `std::vector<ReferrerIntent>`.
- `MergedConfiguration` -> C++ class wrapping global and override configurations.
- `ActivityClientRecord` -> Opaque pointer or reference to the client record structure in C++.

### Memory Management
- The lists (`mPendingResults`, `mPendingNewIntents`) are owned by the item.
- `mActivityClientRecord` is a reference to a system-managed object, likely tied to the app's internal bookkeeping.

### Serialization
- `Parcel::writeTypedList` in C++ needs to handle vectors of Parcelables.

## Implementation Risks
- **Lifecycle Ordering**: `preExecute` sets up state (`mActivityClientRecord`) that `execute` relies on. If `preExecute` is skipped or fails, `execute` must handle the null record gracefully.
- **Null Handling**: `mPendingResults` and `mPendingNewIntents` can be null.
