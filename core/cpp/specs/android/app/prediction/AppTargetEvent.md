# AppTargetEvent - Reverse Engineering Documentation

## Executive Summary
`AppTargetEvent` represents an action taken on a specific `AppTarget`. It records what happened (e.g., launch, dismiss, pin) and where it happened (launch location).

## Architecture Overview
*   **Type**: Data Transfer Object (DTO).
*   **Interface**: Implements `android.os.Parcelable`.

## Detailed Functionality

### Constants (Action Types)
*   `ACTION_LAUNCH` (1)
*   `ACTION_DISMISS` (2)
*   `ACTION_PIN` (3)
*   `ACTION_UNPIN` (4)
*   `ACTION_UNDISMISS` (5)

### Data Holding
**Attributes**:
*   `mTarget` (AppTarget): The subject of the event.
*   `mLocation` (String): ID/Name of the UI surface/location.
*   `mAction` (int): One of the constants above.

## Data Model

| Java Field | Type | C++ Equivalent | Description |
| :--- | :--- | :--- | :--- |
| `mTarget` | `AppTarget` | `AppTarget` struct | The target. |
| `mLocation` | `String` | `std::string` | Launch location. |
| `mAction` | `int` | `int32_t` | Action type enum. |

## API Reference

### Getters
*   `getTarget()`, `getLaunchLocation()`, `getAction()`.

## Java-to-C++ Translation Guide

### Serialization
**Write Order**:
1.  `mTarget` (Parcelable)
2.  `mLocation` (String)
3.  `mAction` (Int)

## Test Cases & Validation
*   **Enum Integrity**: Ensure C++ enums match the integer values (1-5).
*   **Parceling**: Verify nested `AppTarget` serialization works within this event.

## Implementation Risks
*   **Nullable**: `mTarget` and `mLocation` are `@Nullable` in constructors/fields, but usually expected to be populated. Serialization handles nulls via `writeParcelable` (flags) and `writeString`.
