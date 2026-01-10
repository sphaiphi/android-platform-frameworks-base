# TranslationManager - Reverse Engineering Documentation

## Executive Summary
The primary system service manager class (`Context.TRANSLATION_MANAGER_SERVICE`) for client apps to interact with the Translation framework. It handles creating `Translator` sessions, querying capabilities, and managing UI translation updates.

## Architecture
*   **Service Wrapper**: Wraps `ITranslationManager` (Binder interface to system server).
*   **Session Management**: Generates unique `Translator` IDs (`mTranslatorIds`) and manages their lifecycle.
*   **Callbacks**: Maintains a map of listeners for capability updates (`mCapabilityCallbacks`).

## Key Algorithms
*   **`createOnDeviceTranslator`**:
    1.  Generates a random ID.
    2.  Instantiates a `Translator` object.
    3.  The `Translator` constructor asynchronously binds to the backend service.
    4.  Callback receives the initialized `Translator`.
*   **`getOnDeviceTranslationCapabilities`**:
    1.  Uses `SynchronousResultReceiver` to make a blocking call to the system server.
    2.  Waits for result (timeout 60s).
    3.  Deserializes `ParceledListSlice` of capabilities.
*   **`addOnDeviceTranslationCapabilityUpdateListener`**:
    1.  Registers an `IRemoteCallback` with the system server.
    2.  Dispatches updates to the provided `Executor` and `Consumer`.

## Java-to-C++ Translation Guide
*   **Binder**: Heavily relies on Android Binder (`ITranslationManager`, `IRemoteCallback`, `ResultReceiver`). C++ equivalents are `BpTranslationManager`, etc.
*   **Concurrency**: Uses `Handler`, `Executor`, `SynchronousResultReceiver`. C++ would use `ALooper`, `std::future`, or binder callbacks.
