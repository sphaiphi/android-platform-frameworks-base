# PrepareGetCredentialResponse - Reverse Engineering Documentation

## Executive Summary
`PrepareGetCredentialResponse` is the result of the `prepareGetCredential` API. It allows the app to check if credentials exist (e.g., to show a "Sign in" button vs "Sign up") and holds a handle to launch the full retrieval flow later.

## Architecture Overview
- **Type**: Wrapper class (Not Parcelable itself, but holds a handle).
- **Role**: Optimization/UX hint.

## Detailed Functionality

### Core Components
- **`mResponseInternal` (`PrepareGetCredentialResponseInternal`)**: The Parcelable data from the system service.
- **`mPendingGetCredentialHandle` (`PendingGetCredentialHandle`)**: A handle class containing the `PendingIntent` and the transport logic to invoke it.

### Query Methods
- `hasCredentialResults(String type)`: Checks if credentials of a specific type exist.
- `hasAuthenticationResults()`: Checks if locked providers exist.
- `hasRemoteResults()`: Checks if remote devices are available.

### Pending Handle (`PendingGetCredentialHandle`)
- Holds the `PendingIntent` (UI) and the `GetCredentialTransportPendingUseCase` (Callback logic).
- **`show(...)`**: The method to actually launch the UI. It takes the `Context` and `Callback`.

## PrepareGetCredentialResponseInternal
- **Type**: Parcelable.
- **Fields**:
    - `mHasQueryApiPermission` (boolean): Security check result.
    - `mCredentialResultTypes` (`Set<String>`): Types that have results.
    - `mPendingIntent`: The UI intent.

## Java-to-C++ Translation Guide
- **Handle Logic**: The "Handle" pattern separates the *data check* from the *action*. In C++, this might be an object with `has_results()` methods and a `launch()` method.
- **Callbacks**: The `show` method takes a callback. In C++, this would be an async function accepting a completion handler.

## Data Model
```cpp
struct PrepareGetCredentialResponse {
    bool has_query_permission;
    std::set<std::string> result_types;
    // The handle logic implies holding onto the binder/pending intent
    // to invoke the second phase.
};
```
