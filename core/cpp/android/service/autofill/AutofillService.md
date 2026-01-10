# AutofillService - Reverse Engineering Documentation

## Executive Summary
`AutofillService` is the abstract base class for services that provide autofill capabilities (filling user data into views). It interacts with the `AutofillManager` and the system server to receive fill and save requests.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IAutoFillService.Stub` to handle callbacks from the system.
*   **Manifest Requirements**: Must require `android.permission.BIND_AUTOFILL_SERVICE` and declare `android.service.autofill.AutofillService` action.
*   **Workflow**:
    1.  User focuses a view.
    2.  System binds to service.
    3.  Service receives `onFillRequest` with `FillRequest` (containing `AssistStructure`).
    4.  Service responds via `FillCallback.onSuccess` with `FillResponse`.
    5.  User selects data -> UI filled.
    6.  User submits -> `onSaveRequest` called if data needs saving.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Binds the service.
**Logic**: Checks for `SERVICE_INTERFACE` ("android.service.autofill.AutofillService") and returns the internal `IAutoFillService` binder.

### `IAutoFillService.Stub` Implementation
Handles IPC calls and dispatches them to the main thread via `mHandler`.
*   **`onConnectedStateChanged`**: Calls `onConnected()` or `onDisconnected()`.
*   **`onFillRequest`**: Dispatches to `onFillRequest` with `FillRequest`, `CancellationSignal`, and `FillCallback`.
*   **`onSaveRequest`**: Dispatches to `onSaveRequest` with `SaveRequest` and `SaveCallback`.
*   **`onConvertCredentialRequest`**: Dispatches to `onConvertCredentialRequest` (internal/system use).
*   **`onFillCredentialRequest`**: Internal variant.
*   **`onSavedPasswordCountRequest`**: Dispatches to `onSavedDatasetsInfoRequest`.
*   **`onSessionDestroyed`**: Dispatches to `onSessionDestroyed`.

### Core Abstract Methods
*   **`onFillRequest(FillRequest, CancellationSignal, FillCallback)`**:
    *   **Goal**: Analyze view structure, find autofillable fields, return `Dataset`s in a `FillResponse`.
    *   **Parameters**:
        *   `FillRequest`: Contains `AssistStructure` (view hierarchy), `ClientState`.
        *   `CancellationSignal`: To listen for cancel requests.
        *   `FillCallback`: To send `FillResponse` or error.
*   **`onSaveRequest(SaveRequest, SaveCallback)`**:
    *   **Goal**: Save user-entered data.
    *   **Parameters**:
        *   `SaveRequest`: Contains `FillContext`s (snapshots of screen state) and `ClientState`.
        *   `SaveCallback`: To confirm save or show UI.

### Lifecycle Methods
*   `onConnected()`: Initialization hook.
*   `onDisconnected()`: Cleanup hook.
*   `onSessionDestroyed(FillEventHistory)`: Called when autofill session ends.

### Optional Methods
*   `onSavedDatasetsInfoRequest(SavedDatasetsInfoCallback)`: For settings UI to query saved password counts/info.
*   `onConvertCredentialRequest(...)`: For Credential Manager interop.

## Data Model References (Key Classes)
*   **`FillRequest`**: Request data.
*   **`FillResponse`**: The result, containing `Dataset`s and `SaveInfo`.
*   **`Dataset`**: A set of values to fill a group of views (e.g., a username/password pair).
*   **`SaveInfo`**: Configuration for how/when to save data.
*   **`AutofillId`**: Uniquely identifies a view.
*   **`AutofillValue`**: The value (text, date, toggle, list) to fill.

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IAutoFillService.Stub` anonymous class.
*   **C++**: `BnAutoFillService`.

### Threading
*   **Java**: Explicitly uses `Handler` to move work from Binder thread to Main thread.
*   **C++**: Depends on the service architecture. If single-threaded, need a message loop. If multi-threaded, can process on binder thread but must synchronize state.

### View Structure
*   **Java**: `AssistStructure` is the core data object.
*   **C++**: This is a complex parcelable. Accessing it might require significant scaffolding or using existing native definitions if available (Autofill has some native components, but `AssistStructure` is largely Java-managed in framework, though serialized via Parcel).

## Implementation Risks
*   **Timeouts**: The system enforces timeouts on `onFillRequest`.
*   **State Management**: The service is stateless between calls (mostly) but needs to pass `ClientState` (Bundle) to maintain context between Fill and Save requests.
*   **Security**: Handling sensitive user data (passwords, credit cards).
