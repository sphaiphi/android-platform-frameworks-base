# CacheQuotaService - Reverse Engineering Documentation

## Executive Summary
`CacheQuotaService` is an abstract base class for a Service that computes cache quotas for apps. System services bind to this service, send a list of `CacheQuotaHint` requests, and the service returns the list with updated quota values.

## Architecture Overview
- **Type**: Android `Service`.
- **Communication**: Binder IPC via `ICacheQuotaService.aidl`.
- **Threading**: Uses a `Handler` (`ServiceHandler`) on the Main Looper to process requests.
- **Pattern**: Asynchronous callback. The request comes in via Binder, is posted to the main thread, processed by the abstract `onComputeCacheQuotaHints` method, and the result is returned via a `RemoteCallback`.

## Detailed Functionality

### Service Lifecycle
1.  **onCreate**: Initializes the wrapper (`ICacheQuotaService.Stub`) and the `ServiceHandler` (attached to Main Looper).
2.  **onBind**: Returns the wrapper's IBinder.

### Request Processing
1.  **IPC Entry**: `mWrapper.computeCacheQuotaHints` is called by the system.
2.  **Thread Hop**: The wrapper obtains a message `MSG_SEND_LIST` containing the callback and the list of requests, and sends it to the `ServiceHandler`.
3.  **Execution**: `handleMessage` invokes the abstract `onComputeCacheQuotaHints(List<CacheQuotaHint>)`.
4.  **Response**: The result list is wrapped in a `Bundle` (key: `REQUEST_LIST_KEY`) and sent back via `RemoteCallback.sendResult`.

## Data Model
- **Input**: `List<CacheQuotaHint>`
- **Output**: `List<CacheQuotaHint>` (updated)

## API Reference
- `onComputeCacheQuotaHints(List<CacheQuotaHint> requests)`: Abstract method to be implemented by subclasses.

## Java-to-C++ Translation Guide
*Note: Services are typically implemented in Java in Android. If this needs to be C++, it implies a native service implementation.*

- **Binder Interface**: Implement the `ICacheQuotaService` AIDL interface in C++ (`BnCacheQuotaService`).
- **Callback**: Use `android::os::IRemoteCallback` to send the result back.
- **Threading**: Decide if a specific handler thread is needed or if the Binder thread pool is sufficient. Java enforces Main Looper here; C++ might be more flexible.

## Implementation Risks
- **Bundle Handling**: The response is a `Bundle`. C++ `Bundle` handling (via `PersistableBundle` or `BaseBundle`) needs to match the Java expectation. Specifically `putParcelableList`.
