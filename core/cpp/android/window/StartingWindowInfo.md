# StartingWindowInfo - Reverse Engineering Documentation

## Executive Summary
`StartingWindowInfo` contains all necessary information for a `TaskOrganizer` to create and show a starting window (splash screen or snapshot) for a task.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: DTO.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `taskInfo` | `RunningTaskInfo` | Info about the task. |
| `targetActivityInfo` | `ActivityInfo` | Info about the target activity. |
| `startingWindowTypeParameter` | `int` | Flags (New task, process running, snapshot allowed, etc.). |
| `mainWindowLayoutParams` | `WindowManager.LayoutParams` | Layout params of the main window (to match flags/system bars). |
| `taskSnapshot` | `TaskSnapshot` | The snapshot to show (if type is SNAPSHOT). |
| `appToken` | `IBinder` | Token for the window. |
| `windowlessStartingSurfaceCallback` | `IWindowlessStartingSurfaceCallback` | Callback if windowless. |
| `rootSurface` | `SurfaceControl` | Parent surface if windowless. |

## Java-to-C++ Translation Guide

### Data Types
*   `RunningTaskInfo`, `ActivityInfo`, `WindowManager.LayoutParams`, `TaskSnapshot` all need C++ equivalents.

### Parceling
*   Standard write order.

## Implementation Risks
*   **SurfaceControl**: `rootSurface` implies ownership or referencing logic.
