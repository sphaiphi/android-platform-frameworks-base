# SyncNotedAppOp - Reverse Engineering Documentation

## Executive Summary
`SyncNotedAppOp` is an immutable data class that describes a synchronous application operation (AppOp) that was "noted" for the current process. It is used to track permission-protected actions that occur either as a result of a synchronous Binder call or when an app explicitly notes an operation for itself. This is a key part of Android's privacy audit trail.

## Architecture Overview
- **Structure**:
    - `mOpCode`: Integer code for the operation (e.g., `OP_RECORD_AUDIO`).
    - `mOpMode`: The mode returned by the system (e.g., `MODE_ALLOWED`, `MODE_IGNORED`).
    - `mAttributionTag`: Optional tag for the specific feature within the app.
    - `mPackageName`: The package the operation applies to.
- **Inheritance**: Implements `Parcelable`.
- **Identity**: Constructed primarily by the `AppOpsManager`.

## Detailed Functionality

### AppOp Mapping
**Purpose**: Converting internal codes to names.
**Mechanism**: `getOp()` uses `AppOpsManager.opToPublicName(mOpCode)` to return the standardized string identifier.

### Usage Context
**Mechanism**: Delivered via `AppOpsManager.OnOpNotedCallback.onNoted()` after a two-way binder call where the recipient performed a protected operation.

## API Reference
- `public String getOp()`: Returns the public name.
- `public int getOpMode()`: Returns the system's mode.
- `public String getAttributionTag()`: Returns the feature tag.

## Java-to-C++ Translation Guide
- **Data Struct**: Map to a simple C++ `class` with immutable members.
- **Parceling**: Implement `writeToParcel` and `readFromParcel` matching the exact field ordering (`flg`, `opMode`, `opCode`, `attributionTag`, `packageName`).
- **AIDL Integration**: Use the AIDL-generated C++ interface for `SyncNotedAppOp`.

## Implementation Risks
- **Parcel Consistency**: The class explicitly warns: "Native code relies on parcel ordering, do not change". C++ implementations must strictly maintain this order.
- **Range Validation**: Ensure `mOpCode` is within the valid range `[0, AppOpsManager._NUM_OP - 1]`.
