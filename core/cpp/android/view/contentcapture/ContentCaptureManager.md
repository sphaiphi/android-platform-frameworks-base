# ContentCaptureManager - Reverse Engineering Documentation

## Executive Summary
The main system service manager (`Context.CONTENT_CAPTURE_MANAGER_SERVICE`). It manages `ContentCaptureSession`s, communicates with the system server, and provides configuration options.

## Architecture
*   **Service Wrapper**: Wraps `IContentCaptureManager`.
*   **Session Management**: Creates and manages the `MainContentCaptureSession`.
*   **Options**: Holds `ContentCaptureOptions` (logging level, buffer size, etc.).
*   **Data Share**: Logic for `shareData` via `DataShareAdapterDelegate`.

## Key Algorithms
*   **`getMainContentCaptureSession`**: Lazily creates the main session on the UI thread.
*   **`onActivityCreated/Resumed/Paused/Destroyed`**: Activity lifecycle hooks to manage the session state.
*   **`isContentCaptureEnabled`**: Checks options and main session state.

## Java-to-C++ Translation Guide
*   **Binder**: Client-side binder proxy logic.
*   **Threading**: Uses `Handler`s for UI vs Background work.
