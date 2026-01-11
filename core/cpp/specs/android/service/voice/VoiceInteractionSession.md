# VoiceInteractionSession - Reverse Engineering Documentation

## Executive Summary
`VoiceInteractionSession` represents the active user interface and interaction layer of the voice assistant. It is responsible for displaying the assistant panel, receiving assist data (screen context), and providing a bi-directional communication channel between the user and the assistant via voice or UI widgets.

## Architecture Overview
*   **Inheritance**: Not a Service itself, but managed by `VoiceInteractionSessionService`. Implements `KeyEvent.Callback` and `ComponentCallbacks2`.
*   **Window Management**: Uses a specialized `VoiceInteractionWindow` to display content on top of other applications.
*   **IPC**: Implements `IVoiceInteractionSession.Stub`.
*   **Workflow**:
    1.  `VoiceInteractionService` calls `showSession`.
    2.  `VoiceInteractionSessionService` creates the `VoiceInteractionSession`.
    3.  `onShow` is called with arguments and flags (e.g., `SHOW_WITH_ASSIST`).
    4.  The system delivers `AssistStructure` and `AssistContent` via `onHandleAssist`.
    5.  The assistant interacts with the user and finally calls `finish`.

## Detailed Functionality

### UI Creation
*   **`onCreateContentView()`**: Override to provide the view hierarchy for the assistant's UI panel.
*   **`setContentView(View)`**: Sets the content of the assistant's window.

### Assist Data Handling
*   **`onHandleAssist(AssistState)`**: Receives a snapshot of the current application's view hierarchy (`AssistStructure`) and semantic content (`AssistContent`). This allows the assistant to understand "what's on my screen."
*   **`onHandleScreenshot(Bitmap)`**: Receives a screenshot of the foreground activity if `SHOW_WITH_SCREENSHOT` was requested.

### User Interaction
*   **`VoiceInteractor`**: The session provides an `IVoiceInteractor` interface to the foreground activity, allowing the activity to send requests (Confirmation, PickOption, Command) back to the assistant.
*   **`onTaskStarted` / `onTaskFinished`**: Tracks the lifecycle of activities started by the assistant.

### Direct Actions
*   **`requestDirectActions` / `performDirectAction`**: Allows the assistant to query and execute semantic actions defined by the foreground application (e.g., "Add to cart" in a shopping app).

## API Reference

### Constants
*   `SHOW_WITH_ASSIST`: 1
*   `SHOW_WITH_SCREENSHOT`: 2
*   `KEY_SHOW_SESSION_ID`: Identifier for the current session.

## Java-to-C++ Translation Guide

### Windowing
*   **Java**: `VoiceInteractionWindow` (custom dialog).
*   **C++**: Requires interaction with `SurfaceControl` and setting window type to `TYPE_VOICE_INTERACTION`.

### Data Marshalling
*   `AssistStructure` is a massive Parcelable. In C++, parsing this structure requires walking a complex tree of `ViewNode` equivalents.

### Threading
*   Uses `HandlerCaller` to manage messages between the binder thread and the internal session state.

## Implementation Risks
*   **Memory Usage**: `AssistStructure` and screenshots can consume large amounts of memory. The assistant must process and release these quickly.
*   **Z-Order**: The assistant window must appear above all other apps but below system-level overlays.
*   **Concurrency**: The session must handle multiple overlapping assist data callbacks if the user is in a multi-window environment.
