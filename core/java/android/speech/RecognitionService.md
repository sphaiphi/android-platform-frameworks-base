# RecognitionService - Reverse Engineering Documentation

## Executive Summary
`RecognitionService` is an abstract base class for implementing speech recognition services in Android. Developers wishing to provide a custom speech recognizer extend this class. It handles the IPC via `IRecognitionService` binder, session management, and permission checks (audio recording) before delegating the actual recognition work to abstract methods implemented by the subclass.

## Architecture Overview

### Service Structure
- Extends `android.app.Service`.
- Defines `SERVICE_INTERFACE` ("android.speech.RecognitionService").
- Defines `SERVICE_META_DATA` ("android.speech").

### Key Components
- **Binder Interface**: `RecognitionServiceBinder` (extends `IRecognitionService.Stub`). Handles incoming IPC calls (`startListening`, `stopListening`, `cancel`, etc.) and posts them to the service's handler.
- **Session Management**:
    - `mSessions`: A map (`IBinder` -> `SessionState`) tracking active recognition sessions keyed by the client's listener binder.
    - `SessionState`: Holds the client's callback wrapper (`Callback`) and state (e.g., if data delivery has started).
    - `getMaxConcurrentSessionsCount()`: Default is 1. Can be overridden to support multiple concurrent sessions.
- **Callback Wrapper**: `Callback` (inner class). Wraps the `IRecognitionListener` IPC proxy. It provides a local API for the service implementation to send updates to the client (e.g., `results`, `error`, `beginningOfSpeech`). It handles attribution sources for permission checks.
- **Handler**: `mHandler` processes messages on the main thread (UI thread) to ensure thread safety for the service implementation.

### Request Flow
1.  Client calls `SpeechRecognizer.startListening()`.
2.  Binder call `IRecognitionService.startListening()` lands in `RecognitionServiceBinder`.
3.  Binder posts `MSG_START_LISTENING` to `mHandler`.
4.  `dispatchStartListening()` is executed on main thread:
    - Checks concurrency limit.
    - Checks permissions (RECORD_AUDIO) via `PermissionChecker` and `AttributionSource`.
    - Creates a new `SessionState`.
    - Calls abstract `onStartListening(Intent, Callback)`.

## Detailed Functionality

### Abstract Methods (To be implemented)
- `onStartListening(Intent, Callback)`: Begin recognition.
- `onStopListening(Callback)`: Stop capturing audio, finish recognition.
- `onCancel(Callback)`: Cancel recognition immediately.

### Support Methods
- `onCheckRecognitionSupport(...)`: Check if the intent is supported.
- `onTriggerModelDownload(...)`: Trigger model download.
- `createContext(...)`: Overridden to handle attribution context creation for permission checks.

### Inner Classes
- **Callback**: Bridges the service logic to the `IRecognitionListener`. It proxies methods like `results()`, `error()`, `partialResults()` to the client via Binder.
- **SessionState**: Tracks the state of a session.
- **SupportCallback**: Wrapper for `IRecognitionSupportCallback`.

## Java-to-C++ Translation Guide

### Architecture
- This is a Service framework. In C++, this corresponds to implementing a Binder service `BnRecognitionService`.

### IPC
- **IRecognitionService**: Interface to implement.
- **IRecognitionListener**: Interface to call (proxy).

### Threading
- The Java implementation relies heavily on `Handler` (Looper) to serialize access to `mSessions` and to call abstract methods on the main thread.
- **C++**: Use `ALooper` or a worker thread with a message queue to achieve similar serialization.

### Permission Checks
- Java uses `PermissionChecker` and `AttributionSource`.
- **C++**: Requires interactions with PermissionController/AppOps via Binder to verify `RECORD_AUDIO` permission for the caller's UID/PID.

### State Management
- Replicate the `SessionState` map to track multiple clients if concurrency is supported.
- Map `IBinder` (client listener) to session data.
