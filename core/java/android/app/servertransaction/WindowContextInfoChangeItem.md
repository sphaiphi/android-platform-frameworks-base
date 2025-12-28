# WindowContextInfoChangeItem - Reverse Engineering Documentation

## Executive Summary
`WindowContextInfoChangeItem` delivers configuration updates to a `WindowContext` (a non-activity context associated with a window, like an overlay).

## Architecture Overview
- **Inheritance**: Extends `ClientTransactionItem`.
- **Role**: WindowContext update.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `execute`
**Purpose**: Updates info.
**Algorithm**:
1. `client.handleWindowContextInfoChanged(mClientToken, mInfo)`.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mClientToken` | `IBinder` | Token identifying the WindowContext. |
| `mInfo` | `WindowContextInfo` | New config and display ID. |

### Serialization (Parcelable)
- Standard read/write.

## Java-to-C++ Translation Guide

### Data Structures
- `WindowContextInfo` -> C++ equivalent.

## Implementation Risks
- None specific.
