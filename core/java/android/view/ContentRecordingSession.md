# ContentRecordingSession - Reverse Engineering Documentation

## Executive Summary
`ContentRecordingSession` describes a session for recording or mirroring screen content. It specifies whether an entire display or a specific task is being recorded, identifies the target, and tracks user consent status.

## Data Model

### Recording Targets
*   **`RECORD_CONTENT_DISPLAY`**: Records everything visible on a logical display.
*   **`RECORD_CONTENT_TASK`**: Records only the windows belonging to a specific task (app).

### Identifiers
*   **`mVirtualDisplayId`**: The ID of the `VirtualDisplay` where the recorded content is being rendered.
*   **`mDisplayToRecord`**: The ID of the source display (used if recording a display).
*   **`mTokenToRecord`**: The `WindowContainerToken` of the task (used if recording a task).
*   **`mTaskId`**: The numeric ID of the task.

## Detailed Functionality
*   **Consent Tracking**: `mWaitingForConsent` indicates if the session is paused pending user approval.
*   **Validation**: `isValid()` ensures that either a valid display ID or a valid task token is provided.

## Java-to-C++ Translation Guide
*   **Data Class**: This is a pure data carrier. In C++, implement as a `struct` with a `flatten`/`unflatten` method for Parcel support.
*   **Token Handling**: `mTokenToRecord` is an `IBinder`, which maps directly to `sp<IBinder>` in C++.

## Implementation Risks
*   **Security**: Incorrectly specifying the `targetUid` or `token` could lead to recording content from an unauthorized app.
*   **Sync**: The session state must be synchronized between the `DisplayManager` and `WindowManager`.
