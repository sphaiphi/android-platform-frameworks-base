# CredentialManager - Reverse Engineering Documentation

## Executive Summary
`CredentialManager` is the centralized system service for managing user authentication credentials in Android. It provides a unified API for apps to sign in users (Get Credential), register new credentials (Create Credential), and manage credential sessions. It abstracts the underlying providers (Password Managers, Passkeys, etc.) and handles the UI flows for user consent and selection.

## Architecture Overview
- **Role**: System Service (`Context.CREDENTIAL_SERVICE`).
- **Communication**: Uses Binder IPC (`ICredentialManager`) to communicate with the `CredentialManagerService` in the system server.
- **Pattern**: Proxy/Manager pattern. It wraps the IPC calls and handles the async callback translation (Binder callbacks -> `Executor` + `OutcomeReceiver`).
- **Threading**: Heavy reliance on `Executor` for asynchronous callback delivery.
- **Transports**: Uses internal static inner classes (e.g., `GetCredentialTransport`, `CreateCredentialTransport`) extending AIDL Stub interfaces to receive callbacks from the system server.

## Detailed Functionality

### 1. Get Credential (`getCredential`)
**Purpose**: Retrieves a credential for the user, potentially launching UI.
**Mechanism**:
1.  Validates inputs (`GetCredentialRequest`, `Context`, `Executor`, `Callback`).
2.  Checks `CancellationSignal`.
3.  Calls `mService.executeGetCredential` with a `GetCredentialTransport`.
4.  **Transport Logic**:
    - `onPendingIntent`: Launches the `PendingIntent` (UI) via `mContext.startIntentSender`.
    - `onResponse`: Delivers `GetCredentialResponse` to the `OutcomeReceiver`.
    - `onError`: Delivers `GetCredentialException`.

### 2. Create Credential (`createCredential`)
**Purpose**: Registers a new credential.
**Mechanism**:
1.  Validates inputs.
2.  Calls `mService.executeCreateCredential` with a `CreateCredentialTransport`.
3.  **Transport Logic**: Similar to `getCredential`, handles UI via `PendingIntent` or direct success/failure.

### 3. Prepare Get Credential (`prepareGetCredential`)
**Purpose**: Prefetches credential metadata to reduce latency for the subsequent `getCredential` call.
**Mechanism**:
1.  Calls `mService.executePrepareGetCredential`.
2.  Returns a `PrepareGetCredentialResponse` which contains a handle (`PendingGetCredentialHandle`).
3.  The handle can be used later to trigger the full UI flow.

### 4. Clear Credential State (`clearCredentialState`)
**Purpose**: Clears the credential session (e.g., on user logout).
**Mechanism**:
1.  Calls `mService.clearCredentialState`.
2.  No UI involved, just success/error callback.

### 5. Credential Description Registry (`registerCredentialDescription` / `unregister...`)
**Purpose**: Allows providers to register active credentials for filtering/querying.
**Mechanism**: Direct Binder calls to `mService`.

## Data Model
- **`GetCredentialRequest`**: Encapsulates options for retrieval.
- **`CreateCredentialRequest`**: Encapsulates data for creation.
- **`CredentialOption`**: Specific type of credential being requested.
- **`Credential`**: The result object containing the authenticated data.

## API Reference

### Public Methods
- `getCredential(...)`: Async retrieval.
- `createCredential(...)`: Async creation.
- `clearCredentialState(...)`: Async cleanup.
- `prepareGetCredential(...)`: Async prefetch.
- `registerCredentialDescription(...)` / `unregisterCredentialDescription(...)`: Registry management.
- `isServiceEnabled(...)`: Checks availability.

### Hidden/Test Methods
- `setEnabledProviders`: For settings apps to configure providers.
- `getCredentialProviderServices`: Discovery of available providers.

## Java-to-C++ Translation Guide

### IPC & Binder
- **Java**: `ICredentialManager mService` (AIDL interface).
- **C++**: Need `BpCredentialManager` (or equivalent generated from AIDL) to make remote calls.
- **Callbacks**:
    - Java uses anonymous inner classes extending `I[Name]Callback.Stub`.
    - C++ should use `Bn[Name]Callback` implementation to receive IPC callbacks.

### Async Patterns
- **Java**: `Executor` + `OutcomeReceiver<Result, Exception>`.
- **C++**: Use `std::function` callbacks, `std::future`, or a custom Listener interface. Ensure thread safety when invoking callbacks.

### Context & UI
- **Java**: Uses `Context` to start Activities (`startIntentSender`).
- **C++**: The C++ framework layer usually doesn't start Activities directly. This logic might need to stay in Java or use a bridge to the WindowManager/ActivityManager if implemented in native logic (unlikely for the UI launching part).
    - *Note*: The C++ implementation of `CredentialManager` will likely be a client library wrapping the Binder calls. The UI launching logic (`startIntentSender`) is Android-specific and heavily tied to `Context`.

### Error Handling
- **Java**: Exceptions (`GetCredentialException`, etc.) with types and messages.
- **C++**: `std::expected` or specific Error classes/structs matching the Java exception fields (`mType`, `mMessage`).

### constants
- `PROVIDER_FILTER_*`: Int constants. Map to C++ `enum` or `constexpr`.

## Implementation Risks
- **PendingIntent Handling**: Java `IntentSender` logic is complex. C++ side might just pass the `PendingIntent` object up to a Java layer or handle it via specific AM calls.
- **Thread Safety**: Callbacks come from Binder pool threads. Dispatching to the user-provided Executor (or Main thread) is critical.

## Questions for C++ Team
- Will the C++ `CredentialManager` be responsible for launching UI (`PendingIntent`), or will it just expose the `PendingIntent` to the caller? (Likely the latter, as C++ UI launching is rare in this layer).
