# SoundTriggerModule - Reverse Engineering Documentation

## Executive Summary
`SoundTriggerModule` is the primary interface for interacting with a specific piece of sound trigger hardware. It provides methods to load/unload sound models, start/stop recognition, and manage per-model parameters. It acts as a client-side proxy for the native `ISoundTriggerModule` binder interface.

## Architecture Overview
- **Type**: Hardware Proxy.
- **Binder Interaction**: Wraps `ISoundTriggerModule`.
- **Event Handling**: Uses `EventHandlerDelegate` (extending `ISoundTriggerCallback.Stub`) to receive callbacks from the HAL and dispatch them to the application's thread via a `Handler`.
- **Authorization**: Supports both "Originator" (direct app) and "Middleman" (proxy service) identities.

## Detailed Functionality

### Sound Model Management
**Purpose**: To manage the lifecycle of sound patterns in hardware memory.
**Methods**:
- `loadSoundModel(SoundModel, int[])`: Sends the binary model data to the HAL. Returns a numeric handle for the loaded model.
- `unloadSoundModel(int)`: Removes the model from hardware.

### Recognition Control
**Purpose**: To toggle active listening.
**Methods**:
- `startRecognition(int, RecognitionConfig)`: Begins low-power listening for the model associated with the handle.
- `stopRecognition(int)`: Ceases listening.

### Parameter Tuning
**Purpose**: To adjust engine sensitivity or other vendor parameters dynamically.
**Methods**:
- `setParameter(int, int, int)`: Set a value (e.g., `THRESHOLD_FACTOR`).
- `getParameter(int, int)`: Retrieve the current value.
- `queryParameter(int, int)`: Check supported range for a parameter.

## Data Model

### Internal State
- `mId`: The hardware module ID.
- `mService`: Reference to the `ISoundTriggerModule` binder.
- `mEventHandlerDelegate`: Bridge between Binder callbacks and Java `StatusListener`.

## API Reference

### Public Methods
- `void detach()`: Disconnect from hardware and release resources.
- `int getModelState(int)`: Force an asynchronous status update for a model.

## Java-to-C++ Translation Guide

### Threading Model
- **Java**: Uses `Looper` and `Handler` for thread-safe callback dispatch.
- **C++**: Use an `android::Looper` or a dedicated callback thread pool. Avoid processing heavy logic inside the Binder thread (`BnSoundTriggerCallback`).

### Lifecycle Management
- **Java**: Uses `finalize()` to ensure `detach()` is called.
- **C++**: Use RAII. The destructor should automatically call `detach()` and `unlinkToDeath()`.

### Identity Handling
- **Java**: Uses `ClearCallingIdentityContext` and `Identity` objects for permission checks.
- **C++**: Use `android::IPCThreadState` to manage calling UID/PID and verify permissions against the `PermissionCache`.

## Test Cases & Validation
1. **Model Persistence**: Load a model, stop/start recognition multiple times, and verify that the model remains loaded.
2. **Handle Uniqueness**: Load two different models and ensure the HAL returns unique handles for each.
3. **Parameter Bounds**: Try to set a parameter outside the range returned by `queryParameter` and verify it returns `STATUS_BAD_VALUE`.

## Implementation Risks
- **Race Conditions**: Starting recognition immediately after loading (or vice-versa) might lead to transient errors if the HAL is not ready. C++ implementation should include robust retry or state-check logic.
- **Memory Leaks**: If `detach()` is not called, the HAL might keep models loaded indefinitely, eventually leading to `STATUS_BUSY` for other clients.
