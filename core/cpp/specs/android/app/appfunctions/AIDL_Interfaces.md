# AppFunction AIDL Interfaces - Reverse Engineering Documentation

## Executive Summary
This document covers the AIDL interfaces defining the IPC contract for App Functions.

## 1. IAppFunctionManager.aidl
**Role**: System Service Interface.
**Methods**:
-   `executeAppFunction`: Executes a function. Returns `ICancellationSignal`.
-   `setAppFunctionEnabled`: Sets enabled state.

## 2. IAppFunctionService.aidl
**Role**: Application Service Interface.
**Methods**:
-   `executeAppFunction`: Invoked by system on the app.
    -   Inputs: Request, Package, SigningInfo, CancellationCallback, ResultCallback.

## 3. IExecuteAppFunctionCallback.aidl
**Role**: Result reporting.
**Methods**:
-   `onSuccess(ExecuteAppFunctionResponse)`
-   `onError(AppFunctionException)`

## 4. ICancellationCallback.aidl
**Role**: Cancellation transport exchange.
**Methods**:
-   `sendCancellationTransport(ICancellationSignal)`

## 5. IAppFunctionEnabledCallback.aidl
**Role**: Async result for void operations (set enabled).
**Methods**:
-   `onSuccess()`
-   `onError(ParcelableException)`

## Java-to-C++ Translation Guide
-   **AIDL**: Use standard AIDL-to-C++ generator.
-   **Data Types**: Ensure Parcelables (`ExecuteAppFunctionRequest`, etc.) are correctly mapped.

## Implementation Risks
-   **One-way**: `IExecuteAppFunctionCallback` is `oneway`; `IAppFunctionService` is `oneway`. This means async dispatch.
