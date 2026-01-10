# WindowContextInfo - Reverse Engineering Documentation

## Executive Summary
`WindowContextInfo` is a simple Parcelable DTO that groups a `Configuration` and a `displayId`. It is used to inform a `WindowContext` (client-side) about the window state it is currently associated with.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Info DTO.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mConfiguration` | `Configuration` | Current configuration of the associated window. |
| `mDisplayId` | `int` | Current display ID. |

## Java-to-C++ Translation Guide
*   Standard DTO translation.

## Implementation Risks
*   None.
