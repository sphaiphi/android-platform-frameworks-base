# RemoteInputConnectionImpl - Reverse Engineering Documentation

## Executive Summary
The client-side implementation of `IRemoteInputConnection.Stub`. It receives IPC calls from the IME (system process or other app) and dispatches them to the local `InputConnection` on the correct Looper thread.

## Architecture
*   **Dispatcher**: Marshals calls to the View's handler.
*   **Weak Reference**: Holds `mServedView` weakly.
*   **Batch Edit Handling**: Includes safeguards for broken `endBatchEdit` implementations.

## Java-to-C++ Translation Guide
*   **Binder Stub**: Server-side of the IPC (from the perspective of the IME).
*   **Threading**: Critical thread dispatch logic.
