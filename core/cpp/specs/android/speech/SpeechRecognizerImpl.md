# SpeechRecognizerImpl - Reverse Engineering Documentation

## Executive Summary
`SpeechRecognizerImpl` is the concrete internal implementation of the `SpeechRecognizer` API. It manages the complexities of IPC with the `RecognitionServiceManager` and the specific `RecognitionService`.

## Architecture Overview

### Components
- **Manager Connection**: Connects to `Context.SPEECH_RECOGNITION_SERVICE` (usually `IRecognitionServiceManager`).
- **Session Management**: Calls `manager.createSession()` to obtain an `IRecognitionService` instance.
- **Message Queuing**: Uses `mPendingTasks` (a `LinkedBlockingQueue`) to store commands (start, stop, etc.) if the service connection is not yet established.
- **Handler**: `mHandler` (on Main Looper) processes commands and dispatches them to the service.
- **Listener Wrapper**: `InternalRecognitionListener` (extends `IRecognitionListener.Stub`) receives IPC callbacks and posts them back to the application's `RecognitionListener` on the main thread.

### State Management
- `mService`: The active `IRecognitionService` binder proxy.
- `mOnDevice`: Flag indicating if it's an on-device recognizer.
- `mServiceComponent`: The target service component (if specified).

## Detailed Functionality

### Connection Logic (`connectToSystemService`)
1.  Initializes `mManagerService`.
2.  Determines the `ComponentName` of the recognizer (via Settings or `mServiceComponent`).
3.  Calls `mManagerService.createSession`.
4.  On success, sets `mService` and flushes `mPendingTasks`.

### Command Handling
- Methods like `startListening`, `stopListening`, etc., either post to `mHandler` (if connected) or add to `mPendingTasks` (if connecting).
- Commands are executed via the `mService` proxy.

### Callback Marshalling
- `InternalRecognitionListener` receives Binder calls.
- It uses its own `mInternalHandler` (Main Looper) to ensure the application's `RecognitionListener` is called on the main thread.

## Java-to-C++ Translation Guide

### Threading
- Replicate the main-thread marshalling. Commands should be serialized on a worker thread or looper.
- Callbacks must be dispatched back to the caller's thread or a designated executor.

### IPC Details
- C++ implementation must handle `IRecognitionServiceManager` and `IRecognitionService` Binder interfaces.
- Handle `IBinder::DeathRecipient` to detect service crashes and report `ERROR_CLIENT` or `ERROR_SERVER_DISCONNECTED`.

### Pending Tasks
- A queue of command objects/functions is necessary to handle the "wait for connection" state.
