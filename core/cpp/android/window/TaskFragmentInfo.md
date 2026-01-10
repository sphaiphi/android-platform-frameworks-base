# TaskFragmentInfo - Reverse Engineering Documentation

## Executive Summary
`TaskFragmentInfo` is a Parcelable class providing detailed status information about a `TaskFragment`. It is dispatched to `TaskFragmentOrganizer`s to report changes in visibility, configuration, and the list of activities contained within the fragment.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Status Reporting DTO.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mFragmentToken` | `IBinder` | Client-assigned ID for the fragment. |
| `mToken` | `WindowContainerToken` | WM-assigned token for the container. |
| `mConfiguration` | `Configuration` | Current configuration (bounds, etc.). |
| `mRunningActivityCount` | `int` | Number of activities in the fragment. |
| `mIsVisible` | `boolean` | Visibility state. |
| `mActivities` | `List<IBinder>` | List of child activity tokens (belonging to organizer). |
| `mInRequestedTaskFragmentActivities` | `List<IBinder>` | Activities explicitly requested for this fragment. |
| `mPositionInParent` | `Point` | Top-left corner relative to parent Task. |
| `mIsTaskClearedForReuse` | `boolean` | Flag for task clearing events. |
| `mIsTaskFragmentClearedForPip` | `boolean` | Flag for PiP entry events. |
| `mIsClearedForReorderActivityToFront` | `boolean` | Flag for reordering events. |
| `mMinimumDimensions` | `Point` | Aggregated minWidth and minHeight. |
| `mIsTopNonFishingChild` | `boolean` | True if this is the top non-finishing sibling. |

## Detailed Functionality

### `equalsForTaskFragmentOrganizer(TaskFragmentInfo that)`
**Purpose**: Comparison logic to determine if a status update needs to be sent to the client.
**Algorithm**: Checks all relevant fields including token, visibility, count, activities, position, and minimum dimensions. It ignores some transient configuration fields that aren't "interesting" to the organizer.

## Java-to-C++ Translation Guide

### Data Types
*   `List<IBinder>` -> `std::vector<sp<IBinder>>`.
*   `Point` -> `android::graphics::Point`.

### Parceling
*   Use `writeBinderList` / `readBinderList` logic for activities.
*   Strict adherence to field order is required.

## Implementation Risks
*   **Minimum Dimensions**: These are aggregated from child activities. Ensure the C++ side handles the `Point` as `(minWidth, minHeight)`.
