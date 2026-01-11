# AppFunctionManager - Reverse Engineering Documentation

## Executive Summary
`AppFunctionManager` is the primary system service client for the App Functions feature. It allows applications to execute functions provided by other apps (or themselves) and query/set their enabled state. It acts as a wrapper around the IPC interface `IAppFunctionManager`.

## Architecture Overview
-   **Type**: System Service Manager (Context.APP_FUNCTION_SERVICE).
-   **Role**: Client-side API surface.
-   **Dependencies**:
    -   `IAppFunctionManager` (AIDL Binder Interface): The backing system service.
    -   `AppSearchManager`: Used for indexing and discovering function metadata (implicit dependency via helper classes).
    -   `Context`: For package/user information.

## Detailed Functionality

### 1. Execute App Function (`executeAppFunction`)
**Purpose**: Triggers the execution of a specific app function.
**Algorithm**:
1.  Validates inputs (request, executor, callback).
2.  Constructs an `ExecuteAppFunctionAidlRequest` containing:
    -   The client's `ExecuteAppFunctionRequest`.
    -   User handle.
    -   Calling package name.
    -   Timestamp.
3.  Calls `mService.executeAppFunction` with the AIDL request and an `IExecuteAppFunctionCallback` stub.
4.  **Callback Logic**:
    -   `onSuccess`: Executes client callback `onResult` on the provided executor. Catches RuntimeExceptions.
    -   `onError`: Executes client callback `onError` on the provided executor.
5.  **Cancellation**: Sets the remote cancellation signal on the provided `CancellationSignal`.

**Permissions**: Requires `android.permission.EXECUTE_APP_FUNCTIONS` (conditional on ownership/visibility).

### 2. Check Enabled State (`isAppFunctionEnabled`)
**Purpose**: Checks if a specific function is enabled.
**Algorithm**:
1.  Validates inputs.
2.  Retrieves `AppSearchManager`.
3.  Wraps client callback to translate `AppFunctionNotFoundException` to `IllegalArgumentException`.
4.  Delegates logic to `AppFunctionManagerHelper.isAppFunctionEnabled`.

### 3. Set Enabled State (`setAppFunctionEnabled`)
**Purpose**: Enables, disables, or resets a function's state.
**Algorithm**:
1.  Validates inputs.
2.  Wraps client callback in `IAppFunctionEnabledCallback.Stub` (`CallbackWrapper`).
3.  Calls `mService.setAppFunctionEnabled`.
4.  **Callback Wrapper**: Handles success/error and dispatches to executor. Maps specific Binder exceptions to API exceptions (`IllegalArgumentException`, `SecurityException`).

## Data Model
-   **Constants**:
    -   `APP_FUNCTION_STATE_DEFAULT` (0)
    -   `APP_FUNCTION_STATE_ENABLED` (1)
    -   `APP_FUNCTION_STATE_DISABLED` (2)

## API Reference
-   `executeAppFunction(...)`
-   `isAppFunctionEnabled(...)` (2 overloads)
-   `setAppFunctionEnabled(...)`

## Java-to-C++ Translation Guide
-   **Managers**: In C++, system service access usually involves getting `sp<IServiceName>` via `ServiceManager`.
-   **Callbacks**: Java `OutcomeReceiver` -> C++ `std::function` or specific callback interface.
-   **Binder Stubs**: Java anonymous inner classes for `IExecuteAppFunctionCallback.Stub` -> C++ `BnExecuteAppFunctionCallback` subclassing.
-   **Executors**: C++ will likely use `Looper` or `std::thread` / task runner.

## Test Cases & Validation
-   **Execution**: Call `executeAppFunction`, verify callback invoked (success/error). Verify cancellation signal propagation.
-   **State**: Set state, then check state. Verify access control checks (though mostly server-side).

## Implementation Risks
-   **Callback Lifetimes**: Ensure callback objects kept alive during async binder calls.
-   **Exception Mapping**: Java exceptions from Binder need to be carefully mapped to C++ error codes/results.

## Questions for C++ Team
-   Does the C++ client need to expose the full functionality or just specific parts (e.g. only execution)?
