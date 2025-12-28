# NewIntentItem - Reverse Engineering Documentation

## Executive Summary
`NewIntentItem` delivers new intents to an existing activity (e.g., `singleTop` launch mode). It is often followed by a resume request.

## Architecture Overview
- **Inheritance**: Extends `ActivityTransactionItem`.
- **Role**: Intent delivery.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `execute`
**Purpose**: Delivers intents.
**Algorithm**:
1. Trace `activityNewIntent`.
2. Call `client.handleNewIntent(r, mIntents)`.
3. End trace.

### `getPostExecutionState`
**Logic**: Returns `ON_RESUME` if `mResume` is true, otherwise `UNDEFINED`.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mIntents` | `List<ReferrerIntent>` | List of new intents. |
| `mResume` | `boolean` | Whether to resume the activity after delivery. |

### Serialization (Parcelable)
- Standard read/write.

## Java-to-C++ Translation Guide

### Data Structures
- `List<ReferrerIntent>` -> `std::vector<ReferrerIntent>`.

## Implementation Risks
- **Resume Logic**: The `mResume` flag dictates lifecycle progression. The `TransactionExecutor` uses `getPostExecutionState` to cycle the activity.
