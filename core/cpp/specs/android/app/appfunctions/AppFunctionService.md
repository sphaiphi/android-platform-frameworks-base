# AppFunctionService - Reverse Engineering Documentation

## Executive Summary
Abstract base class for services that expose App Functions. Apps implement this service to handle execution requests from the system.

## Architecture Overview
-   **Inheritance**: `android.app.Service`.
-   **Role**: Service implementation base.
-   **Binder Interface**: `IAppFunctionService.Stub`.

## Detailed Functionality

### Binding
-   `onBind`: Returns `mBinder`.
-   `createBinder`: Creates an `IAppFunctionService.Stub` implementation.

### Execution Flow (`executeAppFunction` implementation)
1.  **Permission Check**: Enforces `BIND_APP_FUNCTION_SERVICE` check on caller.
2.  **Callback Wrapping**: Wraps the raw `IExecuteAppFunctionCallback` in `SafeOneTimeExecuteAppFunctionCallback`.
3.  **Cancellation**: Converts `ICancellationCallback` to `CancellationSignal`.
4.  **Dispatch**: Calls abstract `onExecuteFunction` (to be implemented by app).
5.  **Error Handling**: Catches exceptions from `onExecuteFunction` and reports via callback.

### Abstract API
-   `onExecuteFunction`: The main entry point for apps.

## Data Model
-   `SERVICE_INTERFACE`: "android.app.appfunctions.AppFunctionService"

## API Reference
-   `onExecuteFunction(...)`

## Java-to-C++ Translation Guide
-   This class is for **Apps** (Java/Kotlin). C++ implementation would be relevant if writing a native service, but this is an Android SDK API.
-   If implementing the *caller* side (System Server), see `AppFunctionManager`.

## Test Cases & Validation
-   **Security**: Verify execution fails if caller lacks permission.
-   **Crash Safety**: Verify service doesn't crash if `onExecuteFunction` throws.

## Implementation Risks
-   **Main Thread**: `onExecuteFunction` is called on the main thread; implementations must offload heavy work.
