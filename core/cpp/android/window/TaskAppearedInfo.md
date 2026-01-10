# TaskAppearedInfo - Reverse Engineering Documentation

## Executive Summary
`TaskAppearedInfo` is a Parcelable DTO sent to a `TaskOrganizer` when a task appears. It contains the task's metadata (`RunningTaskInfo`) and its control surface (`Leash`).

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: DTO.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mTaskInfo` | `RunningTaskInfo` | Task metadata. |
| `mLeash` | `SurfaceControl` | Surface for control. |

## Java-to-C++ Translation Guide

### Data Types
*   `RunningTaskInfo` -> C++ Parcelable.
*   `SurfaceControl` -> `android::view::SurfaceControl`.

### Parceling
*   Standard write order.

## Implementation Risks
*   None.
