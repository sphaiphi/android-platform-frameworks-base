# Translator - Reverse Engineering Documentation

## Executive Summary
Represents an active translation session. It is the client-side handle that communicates with the remote Translation Service (via system server).

## Architecture
*   **Binder Transport**:
    *   `mSystemServerBinder`: `ITranslationManager` (System Server).
    *   `mDirectServiceBinder`: `ITranslationDirectManager` (Direct link to Service, optimization).
*   **Initialization**:
    *   Uses `ServiceBinderReceiver` (implementation of `IResultReceiver`) to wait for session creation and the direct binder.
    *   Blocking wait in `ServiceBinderReceiver.getSessionStateResult()` for synchronous creation checks (deprecated path).
    *   Async callback in `createOnDeviceTranslator` path.

## Key Algorithms
*   **`translate`**:
    *   Checks if destroyed.
    *   Calls `mDirectServiceBinder.onTranslationRequest`.
    *   Wraps client callback in `TranslationResponseCallbackImpl` (Stub).
*   **`destroy`**:
    *   Notifies service via `onFinishTranslationSession`.
    *   Cleans up references.

## Java-to-C++ Translation Guide
*   **Binder Interfaces**: Requires implementing Bp classes for `ITranslationDirectManager` and `ITranslationCallback`.
*   **Synchronization**: Uses `CountDownLatch` for waiting on binder establishment.
