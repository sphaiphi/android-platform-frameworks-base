# ResultReceiver - Reverse Engineering Documentation

## Executive Summary
`ResultReceiver` is a generic callback interface for receiving a result from someone, possibly across processes. It wraps an `IResultReceiver` Binder interface.

## Architecture Overview
-   **Pattern**: One-way Callback.
-   **IPC**: Uses `IResultReceiver.aidl`.
-   **Usage**: Often used in `Intent` extras (e.g., for `IntentService` or system API callbacks) where a full AIDL interface is too heavy.

## Data Model
-   `mHandler`: Local handler to post results to (if local).
-   `mReceiver`: Remote proxy (`IResultReceiver`).

## API Reference
-   `send(int resultCode, Bundle resultData)`: Dispatches the result.
-   `onReceiveResult(int code, Bundle data)`: Override this to handle results.

## Java-to-C++ Translation Guide
-   **Equivalent**: `android::os::IResultReceiver` (Binder).
-   **Wrapper**: You might implement a C++ wrapper `ResultReceiver` that holds the `sp<IResultReceiver>` and provides a `send` method.
