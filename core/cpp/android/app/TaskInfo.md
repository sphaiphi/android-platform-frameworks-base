# TaskInfo - Reverse Engineering Documentation

## Executive Summary
`TaskInfo` is a data container used by the `ActivityTaskManager` to store and communicate information about a particular task. It provides a comprehensive snapshot of a task's state, including its identification, running status, component names (base, top, real), display association, configuration, and app compat metadata. This information is essential for task management, recents UI, and system-level window organization.

## Architecture Overview
- **Core Components**:
    - **Identification**: `taskId`, `userId`, `effectiveUid`, `token` (WindowContainerToken).
    - **Components**: `baseIntent`, `baseActivity`, `topActivity`, `origActivity`, `realActivity`.
    - **State**: `isRunning`, `isVisible`, `isFocused`, `isSleeping`.
    - **Display & Layout**: `displayId`, `displayAreaFeatureId`, `positionInParent`, `mBounds`, `lastNonFullscreenBounds`.
    - **Metadata**: `taskDescription`, `topActivityInfo`, `pictureInPictureParams`, `appCompatTaskInfo`.
- **Inheritance**: Plain Java object (parceled manually by `ActivityTaskManager`).

## Detailed Functionality

### Task Lifecycle Identification
**Purpose**: Identifying which apps are involved in a task.
- `baseActivity`: The first activity in the task.
- `topActivity`: The one currently visible.
- `realActivity`: The actual component that started the task (important for aliases).

### Window Configuration
**Purpose**: Describing how the task is rendered.
**Logic**: Includes a full `Configuration` object and `WindowContainerToken` for opaque identification. It tracks windowing mode (fullscreen, freeform, pinned) and activity type (home, recents, assistant).

### Comparison Logic
**Purpose**: Determining when task properties change for UI updates.
- `equalsForTaskOrganizer`: Checks fields critical for system-level task organizers (e.g., PiP params, focus, visibility).
- `equalsForCompatUi`: Checks fields relevant for app compatibility treatments (e.g., bounds, orientation).

### Serialization
**Purpose**: Sending task snapshots across process boundaries.
**Mechanism**: Implements `readTaskFromParcel` and `writeTaskToParcel` for manual marshalling into a `Parcel`.

## API Reference
- `public int getTaskId()`: Returns unique ID.
- `public boolean isVisible()`: Checks visibility.
- `public WindowContainerToken getToken()`: Returns system-level handle.
- `public Configuration getConfiguration()`: Returns layout details.

## Java-to-C++ Translation Guide
- **Data Struct**: Map to a C++ `struct` or `class` with corresponding members.
- **Token Handling**: Map `WindowContainerToken` to the AIDL C++ equivalent.
- **Intent/ComponentName**: Use `android::content::Intent` and `android::content::ComponentName` in the native layer.
- **Parceling**: Implement manual serialization matching the Java field order.

## Implementation Risks
- **Parcel Stability**: The ordering of fields in the parcel is fixed and must be perfectly synchronized with the Java side.
- **Data Freshness**: Since `TaskInfo` is a snapshot, C++ logic must be aware that the actual task state in the system server may have changed.
- **Complexity**: The nested `AppCompatTaskInfo` and `Configuration` objects add significant overhead to serialization.
