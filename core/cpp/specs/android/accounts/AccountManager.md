
# AccountManager - Reverse Engineering Documentation

## Executive Summary
`AccountManager` is the primary public API for interacting with the Android accounts framework. It acts as a client-side interface to the central `AccountManagerService`. Applications use this class to get a list of accounts, request authentication tokens for them, and add new accounts to the device. It provides a level of abstraction over the underlying authenticators and handles the asynchronous communication and UI invocation required for authentication tasks.

## Architecture Overview
*   **System Service Client**: `AccountManager` is the application-facing client for the `IAccountManager` system service. It is obtained via `Context.getSystemService(Context.ACCOUNT_SERVICE)`. All of its methods ultimately translate into IPC (Binder) calls to the `AccountManagerService`.
*   **Asynchronous by Default**: Most of its core methods (`getAuthToken`, `addAccount`, `hasFeatures`, etc.) are asynchronous. They return an `AccountManagerFuture` object immediately and accept an optional `AccountManagerCallback`. This design prevents blocking the calling thread (especially the main UI thread) while waiting for IPC, network requests, or user input.
*   **`AccountManagerFuture`**: This is a key abstraction, similar to `java.util.concurrent.Future`. It represents a pending result. A developer can either pass a callback to be invoked when the result is ready or call `future.getResult()` to block and wait for it.
*   **UI Interaction Broker**: When an authentication operation requires user interaction (e.g., to enter a password or grant permissions), `AccountManager` mediates this. It can either start the required `Activity` directly (if an `Activity` context is provided) or return an `Intent` in the result `Bundle`, which the application is responsible for launching.
*   **Caching**: The class includes internal, process-local caches (`mAccountsForUserCache`, `mUserDataCache`) for frequently accessed, semi-static data like the list of accounts and user data. This cache is invalidated by the system service when the underlying data changes, providing a significant performance boost by avoiding repeated IPC calls. The `PropertyInvalidatedCache` mechanism is a specialized Android framework feature for this purpose.

## Detailed Functionality

### Account and Token Retrieval
*   **`getAccounts()` / `getAccountsByType(...)`**: Retrieves a list of `Account` objects visible to the calling application. This is typically the first call an app makes. The data is often served from the local cache.
*   **`getAuthToken(...)`**: The core method for acquiring an authentication token. It has several overloads to handle different scenarios:
    *   **With an `Activity`**: If the call might require UI, providing an `Activity` allows the `AccountManager` to launch the authenticator's login screen directly and seamlessly.
    *   **Without an `Activity` (`notifyAuthFailure`)**: For background tasks. If credentials are required, it can post a notification to the user instead of showing a blocking dialog.
*   **`blockingGetAuthToken(...)`**: A synchronous wrapper around the asynchronous `getAuthToken` call, provided for convenience. It blocks the calling thread and must not be used on the main thread.
*   **`invalidateAuthToken(...)`**: A critical method that applications must call when a server rejects an auth token. This removes the stale token from the `AccountManager`'s cache, ensuring that the next call to `getAuthToken` will attempt to generate a fresh one.

### Account Modification
*   **`addAccount(...)`**: Initiates the flow for adding a new account of a specific type, typically by launching the authenticator's setup `Activity`.
*   **`removeAccount(...)`**: Initiates the flow for removing an account. This may also require user confirmation via an `Activity`.
*   **`addAccountExplicitly(...)` / `setUserData(...)` / `setPassword(...)`**: "Expert" methods intended primarily for use by an authenticator itself to directly manipulate the account data it owns. These methods require the caller's signature to match the authenticator's signature.

### Internal Task Management (`Future2Task`, `AmsTask`)
*   The class uses private inner classes that extend `FutureTask` to manage the asynchronous operations.
*   **`Future2Task` / `AmsTask`**: These classes encapsulate the entire async flow:
    1.  They are created with the user's `Handler` and `Callback`.
    2.  The `doWork()` abstract method is where the specific `mService.someIpcCall()` is made.
    3.  They implement `IAccountManagerResponse.Stub`, creating a Binder object to receive the result from the `AccountManagerService`.
    4.  When `onResult(Bundle)` or `onError(...)` is called by the system, the task translates the result `Bundle` into the final return type (or an exception) and completes the `Future`.
    5.  It then uses the `Handler` to post the `AccountManagerCallback` to the correct thread.

## Data Model
*   `mContext`: The application or activity `Context`.
*   `mService`: The `IAccountManager` Binder proxy for communicating with the system service.
*   `mMainHandler`: A `Handler` tied to the main application looper, used for posting callbacks if no other handler is specified.
*   Caches (`mAccountsForUserCache`, `mUserDataCache`): `PropertyInvalidatedCache` instances for performance.

## Java-to-C++ Translation Guide
*   **Client Library**: `AccountManager` would be a C++ client library. Its public methods would mirror the Java API.
*   **IPC**: The C++ `AccountManager` would hold a `std::shared_ptr` to a `BpAccountManager` proxy object.
*   **Asynchronous Operations**: The `AccountManagerFuture` pattern can be directly replicated using `std::future`. The C++ methods would return a `std::future<ResultType>`.
*   **Callbacks**: C++ callbacks can be implemented using `std::function`. The future-based task would, upon completion, execute the `std::function` on a specified event loop or thread.
*   **Internal Task Management**: The `Future2Task` pattern can be implemented in C++. A C++ task class would:
    *   Hold a `std::promise` to set the value of the `std::future` that was returned to the user.
    *   Implement the `BnAccountManagerResponse` Binder stub.
    *   In its `onResult` implementation, it would call `promise.set_value()`.
    *   In its `onError` implementation, it would call `promise.set_exception()`.
*   **Caching**: The `PropertyInvalidatedCache` is an Android-specific feature. A C++ version could use a standard LRU cache, but it would lack the automatic invalidation mechanism tied to system properties. A custom observer/notification system would be needed to replicate that behavior.

## Implementation Risks
*   **Asynchronous Complexity**: Correctly managing the `std::future` and `std::promise` logic, especially with callbacks and multi-threading, is complex and error-prone.
*   **UI Integration**: The tight integration with the `Activity` lifecycle for showing UI is very Android-specific. A C++ version would need a completely different, platform-specific way to handle UI interactions.
*   **Cache Invalidation**: Without the `PropertyInvalidatedCache` system, a C++ cache could easily become stale, leading to apps working with outdated account information. A robust replacement is critical for performance and correctness.

## Questions for C++ Team
*   What is the standard C++ library for asynchronous task management that should be used to replace `AccountManagerFuture`? (`std::future`, Boost futures, or something else?)
*   How will the C++ `AccountManager` be notified that its caches are stale and need to be invalidated?
*   What is the C++ strategy for launching a UI flow for user credential input, equivalent to returning an `Intent` in the result `Bundle`?
