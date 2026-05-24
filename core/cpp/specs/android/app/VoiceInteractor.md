# VoiceInteractor - Reverse Engineering Documentation

## Executive Summary
`VoiceInteractor` is the primary interface for an `Activity` to interact with the system's voice interaction service (e.g., Google Assistant). It allows apps to submit conversational requests (confirmations, options, generic commands) and receive asynchronous results. It is tightly integrated with the Activity lifecycle and state saving mechanism to ensure conversational continuity across configuration changes.

## Architecture Overview
- **Core Components**:
    - `IVoiceInteractor mInteractor`: The AIDL proxy for the background voice service.
    - `mCallback`: A Binder stub that receives results from the voice service.
    - `mHandlerCaller`: Dispatches callbacks from the Binder thread to the application's main thread.
    - `mActiveRequests`: A map tracking pending requests keyed by their Binder tokens.
- **Request Types**:
    - `ConfirmationRequest`: A simple yes/no question.
    - `PickOptionRequest`: A list of options for the user to choose from.
    - `CompleteVoiceRequest`: Signal that the task is finished.
    - `AbortVoiceRequest`: Signal that the task cannot be completed via voice.
    - `CommandRequest`: A vendor-specific command.

## Detailed Functionality

### Request Submission (`submitRequest`)
**Purpose**: Starts a voice interaction step.
**Algorithm**:
1. Checks if the interactor is still alive.
2. Calls the appropriate `mInteractor.start...` method based on the request type.
3. Maps the returned `IVoiceInteractorRequest` to the local `Request` object.
4. Stores the mapping in `mActiveRequests`.

### Lifecycle Management (`attachActivity` / `detachActivity`)
**Purpose**: Preserves conversational state during Activity restarts.
**Logic**: 
- When an Activity is destroyed due to a configuration change, the interactor is "retained".
- When the new Activity instance is created, `attachActivity` re-links the interactor and all active requests to the new instance.
- This ensures that if a result arrives while the Activity is restarting, it isn't lost.

### Result Delivery
**Mechanism**:
1. Voice service calls a method on `mCallback`.
2. `mCallback` posts a message to `mHandlerCaller`.
3. `mHandlerCallerCallback` retrieves the corresponding `Request` from the map and invokes its `on...Result` method on the main thread.

## API Reference (Key Classes)
- `public abstract static class Request`: Base for all voice operations.
- `public static class Prompt`: Container for spoken and visual text.
- `public boolean submitRequest(Request request)`: Trigger point.
- `public boolean isDestroyed()`: State check.

## Java-to-C++ Translation Guide
- **AIDL Integration**: Use AIDL-generated C++ interfaces `android::app::IVoiceInteractor` and `android::app::IVoiceInteractorCallback`.
- **Request Hierarchy**: Use a C++ polymorphism model for request types.
- **Handler**: Use a native `android::os::Handler` or `Looper` to dispatch results to the main thread.
- **Map Management**: Use `std::unordered_map<android::sp<IBinder>, std::shared_ptr<Request>>`.

## Implementation Risks
- **Identity Leaks**: Requests hold references to the `Activity`. C++ implementation must use weak pointers to avoid preventing Activity destruction.
- **IPC Ordering**: Results might arrive before the submission call returns in some race conditions. The C++ layer must handle synchronization of the request map.
- **Dead Service**: If the voice service process crashes, the `mInteractor` proxy will become invalid. Reconnection logic or graceful failure is needed.
