# DeviceStateManagerGlobal - Reverse Engineering Documentation

## Executive Summary
`DeviceStateManagerGlobal` is a singleton class that manages the Binder IPC connection to the `IDeviceStateManager` system service. It handles callback registration, request token lifecycle, and caching of the most recent `DeviceStateInfo`.

## Architecture Overview
- **Pattern**: Singleton / IPC Proxy
- **Key Components**:
    - `IDeviceStateManager`: The AIDL interface to the service.
    - `mCallbacks`: List of registered listeners.
    - `mRequests`: Map of `IBinder` tokens to active requests.
    - `mLastReceivedInfo`: Caches the latest state to provide immediate updates to new listeners.

## Detailed Functionality

### Singleton Management
- Lazy initialization via `getInstance()`.
- Fetches service via `ServiceManager.getService(Context.DEVICE_STATE_SERVICE)`.

### Request Lifecycle
1.  **Request Submission**:
    - Creates a new `Binder` token for the request.
    - Wraps request + callback + executor.
    - Stores in `mRequests`.
    - Calls `mDeviceStateManager.requestState(token, state, flags)`.
2.  **Cancellation**:
    - Calls `mDeviceStateManager.cancelStateRequest()`.
    - **Note**: The API seems to imply a single active request per client (or global cancellation), but the `mRequests` map suggests tracking multiple tokens. However, `cancelStateRequest()` (singular) on the AIDL interface suggests the service might only track the "top" request per process or generally. *Analysis of AIDL confirms `cancelStateRequest` takes no arguments, implying it cancels the process's active request.*

### Callback Handling
- Maintains a local `DeviceStateManagerCallback` (Stub) that receives AIDL calls.
- Dispatches updates to all registered `DeviceStateCallbackWrapper` instances.
- **Threading**: Marshals calls to the user-provided `Executor`.

## Data Model
- `mRequests`: `ArrayMap<IBinder, DeviceStateRequestWrapper>`
    - Key: Binder token (identity of the request).
    - Value: Wrapper containing the Request object and Callback.

## Java-to-C++ Translation Guide

### IPC
- Use `android::sp<IDeviceStateManager>` for the service interface.
- Implement `BnDeviceStateManagerCallback` for the callback stub.

### Concurrency
- Java uses `synchronized(mLock)`. C++ should use `std::mutex`.
- Java uses `Executor` for callbacks. C++ might use `Looper` or a specific thread pool depending on the client architecture.

### Token Management
- Java uses `new Binder()` as a token. C++ should use `sp<BBinder>` (local binder) as the unique token passed to the server.

## Special Logic
- **Immediate Callback**: When registering a callback, if `mLastReceivedInfo` is cached, it immediately notifies the new listener.
- **Flags**: `wlinfoOncreate()` flag changes whether `registerCallback` returns the info immediately or waits. C++ should support both paths if the flag is relevant to native code, or assume the modern behavior.
