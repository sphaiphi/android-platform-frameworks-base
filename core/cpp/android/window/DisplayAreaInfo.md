# DisplayAreaInfo - Reverse Engineering Documentation

## Executive Summary
`DisplayAreaInfo` is a Parcelable class that contains configuration and identification information for a `DisplayArea`. It is used to inform `DisplayAreaOrganizer`s about the state of the display areas they control.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Info DTO.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `token` | `WindowContainerToken` | Unique identifier for the DA. |
| `configuration` | `Configuration` | The configuration (bounds, etc.) of the DA. |
| `displayId` | `int` | ID of the display. |
| `featureId` | `int` | Feature ID associated with this DA (e.g., FEATURE_ROOT). |
| `rootDisplayAreaId` | `int` | Feature ID of the root DA this DA belongs to. |

## Java-to-C++ Translation Guide

### Data Types
*   `WindowContainerToken` -> C++ Parcelable.
*   `Configuration` -> C++ Parcelable.

### Parceling
*   **Write**:
    1.  `token`
    2.  `configuration`
    3.  `displayId`
    4.  `featureId`
    5.  `rootDisplayAreaId`

## Implementation Risks
*   None. Standard DTO.
