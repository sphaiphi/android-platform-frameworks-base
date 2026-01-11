# MoveToDisplayItem - Reverse Engineering Documentation

## Executive Summary
`MoveToDisplayItem` handles the migration of an activity from one display to another. It includes the configuration update associated with the display change.

## Architecture Overview
- **Inheritance**: Extends `ActivityTransactionItem`.
- **Role**: Multi-display support.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `preExecute`
**Purpose**: Prepares config update.
**Algorithm**:
1. Apply compatibility overrides.
2. Update pending activity configuration.

### `execute`
**Purpose**: Executes the move.
**Algorithm**:
1. Trace `activityMovedToDisplay`.
2. Call `client.handleActivityConfigurationChanged(r, mConfiguration, mTargetDisplayId, mActivityWindowInfo)`.
3. End trace.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mTargetDisplayId` | `int` | ID of the new display. |
| `mConfiguration` | `Configuration` | New configuration. |
| `mActivityWindowInfo` | `ActivityWindowInfo` | New window info. |

### Serialization (Parcelable)
- Standard read/write for fields.

## Java-to-C++ Translation Guide

### Notes
- Similar to `ActivityConfigurationChangeItem` but includes `mTargetDisplayId`.

## Implementation Risks
- **Display Existence**: The target display ID should be valid on the client side, though the item simply carries the ID.
