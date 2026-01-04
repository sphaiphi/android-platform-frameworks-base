# FieldClassificationService - Reverse Engineering Documentation

## Executive Summary
`FieldClassificationService` is an abstract service that allows the system (specifically Autofill Framework) to classify fields on the screen using an `AssistStructure`. Implementations use this to detect field types (e.g., username, password, credit card) to provide autofill suggestions.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Uses `IFieldClassificationService` (AIDL) for system communication.
*   **Permissions**: Requires `android.permission.BIND_FIELD_CLASSIFICATION_SERVICE`.
*   **Asynchronous Model**: Uses `OutcomeReceiver` and `CancellationSignal` for async request handling.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Binds the service to the system.
**Algorithm**:
1.  Verifies the intent action matches `SERVICE_INTERFACE`.
2.  Returns an instance of `IFieldClassificationService.Stub`.

### `IFieldClassificationService.Stub` Implementation
*   **`onConnected(boolean debug, boolean verbose)`**: Updates internal debug/verbose flags and calls `onConnected()`.
*   **`onDisconnected()`**: Calls `onDisconnected()`.
*   **`onFieldClassificationRequest`**: Bridges the AIDL call to the abstract `onClassificationRequest` method, handling `CancellationSignal` creation and `OutcomeReceiver` callbacks.

### `onClassificationRequest` (Abstract)
**Purpose**: The main entry point for processing a classification request.
**Parameters**:
*   `request`: `FieldClassificationRequest` containing the `AssistStructure`.
*   `cancellationSignal`: Allows the system to cancel the operation.
*   `outcomeReceiver`: Callback to return the `FieldClassificationResponse` or an error.
**C++ Implementation Guidance**:
*   Implementations should process the `AssistStructure` (likely traversing the view hierarchy).
*   Should check `cancellationSignal.isCanceled()` periodically during long-running operations.
*   Must call `outcomeReceiver.onResult` or `outcomeReceiver.onError` eventually.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.assist.classification.FieldClassificationService"`

### Lifecycle Methods
*   `void onConnected()`
*   `void onDisconnected()`
*   `void onClassificationRequest(...)`: Abstract.

## Java-to-C++ Translation Guide

### Async Pattern
*   **Java**: Uses `OutcomeReceiver<Result, Error>` and `CancellationSignal`.
*   **C++**: Typically maps to a callback interface (like `IFieldClassificationCallback` in AIDL) and a `ICancellationSignal` binder. The service implementation should hold onto the callback and invoke it when work is done.

### Error Handling
*   **Java**: Catches `RemoteException` and rethrows or logs.
*   **C++**: `binder::Status` returns for AIDL methods.

## Implementation Risks
*   **Performance**: Processing `AssistStructure` can be heavy. Ensure it doesn't block the binder thread if not necessary (though the base class handles the binder thread part, the actual logic might need a worker thread).
*   **Security**: The service receives sensitive screen data via `AssistStructure`. Secure handling is paramount.
