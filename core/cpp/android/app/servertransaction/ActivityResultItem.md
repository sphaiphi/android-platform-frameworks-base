# ActivityResultItem - Reverse Engineering Documentation

## Executive Summary
`ActivityResultItem` delivers result data (from `setResult()` in another activity) to a target activity. It corresponds to the `onActivityResult` callback in the Android application lifecycle.

## Architecture Overview
- **Inheritance**: Extends `ActivityTransactionItem`.
- **Role**: Transports result data.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `execute`
**Purpose**: Delivers the result to the activity.
**Algorithm**:
1. Start tracing `activityDeliverResult`.
2. Call `client.handleSendResult(r, mResultInfoList, "ACTIVITY_RESULT")`.
3. End tracing.

### `getPostExecutionState`
**Purpose**: Determines the state the activity should be in after receiving results.
**Logic**:
- Checks compatibility flag `CALL_ACTIVITY_RESULT_BEFORE_RESUME`.
- If enabled (Android S+), returns `ON_RESUME`.
- Otherwise, returns `UNDEFINED`.
**Java-Specific Notes**:
- Uses `CompatChanges` framework to maintain legacy behavior for older apps.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mResultInfoList` | `List<ResultInfo>` | List of results to deliver. |

### Serialization (Parcelable)
- **Flattening**:
  - Writes parent data.
  - Writes `mResultInfoList` using `writeTypedList`.
- **Unflattening**:
  - Reads parent data.
  - Reads `mResultInfoList` using `createTypedArrayList`.

## API Reference

### `ActivityResultItem(@NonNull IBinder activityToken, @NonNull List<ResultInfo> resultInfoList)`
- **Constructor**: Initializes with token and result list. Creates a defensive copy of the list.

## Java-to-C++ Translation Guide

### Data Structures
- `List<ResultInfo>` -> `std::vector<ResultInfo>`.

### Compatibility Flags
- `CompatChanges.isChangeEnabled(CALL_ACTIVITY_RESULT_BEFORE_RESUME)` needs a C++ equivalent mechanism to check per-app compatibility flags/target SDK versions.

### Serialization
- Handle potential nulls in list reading if `createTypedArrayList` allows it, though constructor enforces `NonNull`.

## Implementation Risks
- **App Compatibility**: The behavior change based on `CALL_ACTIVITY_RESULT_BEFORE_RESUME` is critical for correct lifecycle ordering. The C++ implementation must correctly query this property.
