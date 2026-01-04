# CredentialProviderService - Reverse Engineering Documentation

## Executive Summary
`CredentialProviderService` is the base class for applications that provide user credentials (passwords, passkeys, etc.) to the Android Credential Manager. It enables providers to offer credentials for auto-filling into other apps and to save new credentials created by the user.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `ICredentialProviderService.Stub`.
*   **Threading**: Uses a `Handler` on the main looper to marshal binder calls to abstract service methods.
*   **Manifest Requirements**: Must require `android.permission.BIND_CREDENTIAL_PROVIDER_SERVICE` and declare `android.service.credentials.CredentialProviderService` action.
*   **Two-Stage Workflow**:
    1.  **Begin Phase**: The system binds to the service and calls `onBeginGetCredential` or `onBeginCreateCredential`. The service returns a list of "Entries" (e.g., `CredentialEntry`, `CreateEntry`), each associated with a `PendingIntent`.
    2.  **Selection Phase**: The system displays the entries in a selector UI. When the user picks one, the system launches the `PendingIntent`, which starts an Activity in the provider's process to complete the operation (e.g., biometrics, selection confirmation) and return the final result.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the binder interface for the Credential Manager system service.

### Core Abstract Methods
*   **`onBeginGetCredential(BeginGetCredentialRequest, CancellationSignal, OutcomeReceiver)`**:
    *   **Goal**: Provide candidate credentials for a "get" request.
    *   **Result**: A `BeginGetCredentialResponse` containing `CredentialEntry` objects (to be shown in the selector) and `Action` objects (e.g., "Manage Settings").
*   **`onBeginCreateCredential(BeginCreateCredentialRequest, CancellationSignal, OutcomeReceiver)`**:
    *   **Goal**: Provide options for saving a new credential.
    *   **Result**: A `BeginCreateCredentialResponse` containing `CreateEntry` objects.
*   **`onClearCredentialState(ClearCredentialStateRequest, CancellationSignal, OutcomeReceiver)`**:
    *   **Goal**: Request the provider to clear any active credential sessions (e.g., after a user logs out).

### Key Extras for Completion Activities
The following extras are used when the provider's Activity returns a result to the system:
*   `EXTRA_GET_CREDENTIAL_RESPONSE`: Final result for a get flow.
*   `EXTRA_CREATE_CREDENTIAL_RESPONSE`: Final result for a create flow.
*   `EXTRA_GET_CREDENTIAL_EXCEPTION`: Error result for a get flow.
*   `EXTRA_CREATE_CREDENTIAL_EXCEPTION`: Error result for a create flow.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.credentials.CredentialProviderService"`
*   `SERVICE_META_DATA`: `"android.credentials.provider"` - Points to an XML describing provider capabilities.

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `ICredentialProviderService.Stub`.
*   **C++**: `BnCredentialProviderService`.

### Async Pattern
*   **Java**: Uses `OutcomeReceiver` and `CancellationSignal`.
*   **C++**: The AIDL interface uses callbacks (`IBeginGetCredentialCallback`, etc.). The C++ implementation should hold these callback pointers and invoke them once the result is ready.

### Data Structures
*   `BeginGetCredentialRequest`, `BeginCreateCredentialResponse`, etc., are Parcelables.
*   The system heavily relies on `PendingIntent` to bridge from the service call to the provider's UI.

## Implementation Risks
*   **Performance**: The "Begin" phase must be very fast to avoid delaying the system selector UI.
*   **Security**: Handling sensitive credential data. The provider must ensure that it only returns credentials relevant to the calling app (info provided in `CallingAppInfo`).
*   **Lifecycle**: The service must handle `CancellationSignal` properly to abort long-running queries if the user dismisses the UI.
