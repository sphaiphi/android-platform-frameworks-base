# SmartspaceTargetEvent - Reverse Engineering Documentation

## Executive Summary
`SmartspaceTargetEvent` encapsulates a feedback signal regarding a `SmartspaceTarget`. It is sent from the client to the service to report impressions, clicks, dismissals, and other interactions.

## Architecture Overview
- **Package**: `android.app.smartspace`
- **Type**: `Parcelable` event container.

## Detailed Functionality

### Event Types
Defines interactions:
- `EVENT_TARGET_INTERACTION`: Click/Tap.
- `EVENT_TARGET_SHOWN` / `HIDDEN`: Visibility changes.
- `EVENT_TARGET_DISMISS` / `BLOCK`: Negative feedback.
- `EVENT_UI_SURFACE_SHOWN` / `HIDDEN`: Container visibility.

### Data Holding
**Components**:
- `mSmartspaceTarget`: The target object involved (Nullable).
- `mSmartspaceActionId`: Specific action ID within the target (Nullable).
- `mEventType`: The type integer.

### Serialization
Standard Parcel read/write.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mSmartspaceTarget` | `SmartspaceTarget` | The subject of the event. |
| `mSmartspaceActionId` | `String` | ID of the specific action clicked. |
| `mEventType` | `int` | Type constant. |

## Java-to-C++ Translation Guide
- **Enums**: Replicate `EVENT_*` constants.
- **Nullable**: `SmartspaceTarget` can be null (e.g., for Surface events). C++ should use `std::optional` or `std::unique_ptr` / nullable pointer.

## Test Cases & Validation
1.  **Parceling**: Verify null target/action ID handling during parceling.
