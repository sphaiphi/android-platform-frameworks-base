# RemoteTransition - Reverse Engineering Documentation

## Executive Summary
`RemoteTransition` couples an `IRemoteTransition` (the interface to run an animation) with the `IApplicationThread` of the process hosting it. This allows the system to boost the priority of the transition runner process.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Container for remote animation interface + process identity.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mRemoteTransition` | `IRemoteTransition` | The animation runner interface. |
| `mAppThread` | `IApplicationThread` | The app thread of the runner (for scheduling/boosts). |
| `mDebugName` | `String` | Debugging tag. |

## Java-to-C++ Translation Guide

### Data Types
*   `IRemoteTransition` -> Binder interface.
*   `IApplicationThread` -> Binder interface.

### Parceling
*   **Write**: Flags (for nullables), then interfaces, then name.

## Implementation Risks
*   None.
