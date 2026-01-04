# TaskFragmentTransaction - Reverse Engineering Documentation

## Executive Summary
`TaskFragmentTransaction` encapsulates a set of changes happening to one or more TaskFragments managed by the same organizer. It allows the `WindowManager` to dispatch multiple updates (appearance, info change, removal, errors) in a single atomic IPC message.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Transactional update container.
*   **Inner Class**: `Change`.

## Change Types (IntDef)
*   `TYPE_TASK_FRAGMENT_APPEARED` (1)
*   `TYPE_TASK_FRAGMENT_INFO_CHANGED` (2)
*   `TYPE_TASK_FRAGMENT_VANISHED` (3)
*   `TYPE_TASK_FRAGMENT_PARENT_INFO_CHANGED` (4)
*   `TYPE_TASK_FRAGMENT_ERROR` (5)
*   `TYPE_ACTIVITY_REPARENTED_TO_TASK` (6)

## Data Model (Change)

| Field | Type | Description |
| :--- | :--- | :--- |
| `mType` | `int` | Change identifier. |
| `mTaskFragmentToken` | `IBinder` | Fragment identifier. |
| `mTaskFragmentInfo` | `TaskFragmentInfo` | Fragment metadata. |
| `mTaskId` | `int` | Parent task ID. |
| `mErrorCallbackToken` | `IBinder` | (Optional) Token for error reporting. |
| `mErrorBundle` | `Bundle` | Error metadata. |
| `mActivityIntent` | `Intent` | (Optional) Reparented activity intent. |
| `mActivityToken` | `IBinder` | (Optional) Reparented activity token. |
| `mOtherActivityToken` | `IBinder` | (Optional) Sibling activity token. |
| `mTaskFragmentParentInfo` | `TaskFragmentParentInfo` | Parent task metadata. |
| `mSurfaceControl` | `SurfaceControl` | (Optional) Fragment leash. |

## Java-to-C++ Translation Guide

### Parceling
*   **Transaction**: Writes its token (Binder), then the list of `Change` objects.
*   **Change**: Writes all fields sequentially. Note that many are nullable and use `writeTypedObject` or `writeStrongBinder`.

## Implementation Risks
*   **Error Handling**: The `mErrorBundle` can contain serialized exceptions. C++ should handle these as generic metadata bundles or use a specific error code mapping.
