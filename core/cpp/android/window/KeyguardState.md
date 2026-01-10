# KeyguardState - Reverse Engineering Documentation

## Executive Summary
`KeyguardState` is a Parcelable data object used to transport keyguard visibility state (showing, AOD) within a `WindowContainerTransaction`.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: DTO for WCT operations.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mKeyguardShowing` | `boolean` | Whether the keyguard is currently showing. |
| `mAodShowing` | `boolean` | Whether Always-on Display (AOD) is showing. |

## Java-to-C++ Translation Guide

### Data Types
*   `boolean` -> `bool`.

### Parceling
*   **Write**:
    1.  `mKeyguardShowing`
    2.  `mAodShowing`

## Implementation Risks
*   None.
