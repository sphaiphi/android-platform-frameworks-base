# PinnerServiceClient - Reverse Engineering Documentation

## Executive Summary
`PinnerServiceClient` is a utility class that abstracts the interaction with the system's `PinnerService` (`pinner`). It handles the Binder connection setup and provides a strongly-typed method to retrieve file pinning statistics, including error handling for service unavailability.

## Architecture Overview
*   **Pattern**: Service Proxy / Client Wrapper.
*   **Dependencies**:
    *   `android.os.ServiceManager`: To locate the system service.
    *   `android.app.pinner.IPinnerService`: The AIDL interface definition.
    *   `android.app.pinner.PinnedFileStat`: The data model returned.

## Detailed Functionality

### `getPinnerStats`
**Purpose**: Retrieves a list of currently pinned files and their statistics from the `PinnerService`.
**Algorithm**:
1.  **Service Lookup**: calls `ServiceManager.getService("pinner")`.
2.  **Null Check**: If the service binder is null (service not found or permission denied), logs a warning and returns an empty list.
3.  **Interface Casting**: Converts the `IBinder` object to an `IPinnerService` interface using `Stub.asInterface`.
4.  **Cast Check**: If casting fails, logs a warning and returns an empty list.
5.  **Remote Call**: Invokes `pinnerService.getPinnerStats()`.
6.  **Exception Handling**:
    *   Catch `RemoteException`: Wraps it in a `RuntimeException` and re-throws.
7.  **Return**: Returns the `List<PinnedFileStat>` from the service.

**Java-Specific Notes**:
*   Uses `ServiceManager` which is the standard Android mechanism for finding system services.
*   The service name "pinner" is hardcoded strings.
*   `RemoteException` is a checked exception in Java, requiring explicit handling.

## API Reference

### `getPinnerStats()`
*   **Returns**: `List<PinnedFileStat>` - A list of statistics objects. Returns an empty list if the service cannot be connected (not found/permission denied).
*   **Throws**: `RuntimeException` if a `RemoteException` occurs during the IPC call (i.e., connection established but call failed).

## Java-to-C++ Translation Guide

### Dependencies
*   Include `<binder/IServiceManager.h>`
*   Include generated header for `IPinnerService` (from AIDL).

### Implementation Logic
In C++, the `ServiceManager` interaction is similar but uses strong pointers (`sp`).

```cpp
#include <binder/IServiceManager.h>
#include <android/app/pinner/IPinnerService.h>

std::vector<PinnedFileStat> getPinnerStats() {
    // 1. Get Service Manager
    sp<IServiceManager> sm = defaultServiceManager();
    
    // 2. Get Service Binder
    sp<IBinder> binder = sm->getService(String16("pinner"));
    if (binder == nullptr) {
        // Log warning: "Failed to retrieve PinnerService..."
        return {};
    }

    // 3. Cast to Interface
    sp<IPinnerService> pinnerService = interface_cast<IPinnerService>(binder);
    if (pinnerService == nullptr) {
        // Log warning: "Failed to cast PinnerService."
        return {};
    }

    // 4. Remote Call
    std::vector<PinnedFileStat> stats;
    android::binder::Status status = pinnerService->getPinnerStats(&stats);

    // 5. Error Handling
    if (!status.isOk()) {
        // Java throws RuntimeException here. C++ might log or throw depending on project convention.
        // status.toString8() provides error details.
        // Assuming we propagate error or return empty based on requirements.
        // The Java code crashes the caller (RuntimeException) on RemoteException. 
        // C++ equivalent might be returning a Result<T> or logging fatal.
        return {}; 
    }

    return stats;
}
```

## Test Cases & Validation

### Case 1: Service Available
*   **Precondition**: `PinnerService` is registered and running.
*   **Input**: Call `getPinnerStats()`.
*   **Expected**: Returns a list of `PinnedFileStat` objects populated with real data.

### Case 2: Service Missing (e.g., SELinux denial)
*   **Precondition**: `ServiceManager` returns null for "pinner".
*   **Input**: Call `getPinnerStats()`.
*   **Expected**: Logs warning "Failed to retrieve PinnerService..." and returns empty list.

### Case 3: Remote Exception (e.g., Service crash during call)
*   **Precondition**: Service is returned but dies during `getPinnerStats` execution.
*   **Input**: Call `getPinnerStats()`.
*   **Expected**: `status.isOk()` is false. Java throws `RuntimeException`.

## Implementation Risks
1.  **Permission Model**: The Java code notes "lack of selinux permissions" as a common failure. Ensure the C++ client context has `getattr` permissions on the `pinner` service context in `service_contexts`.
2.  **Thread Safety**: `ServiceManager` and Binder calls are generally thread-safe, but verify the lifecycle of the returned objects.
3.  **Exception Translation**: Java converts `RemoteException` to `RuntimeException`. C++ must decide whether to return a status code, empty list, or abort. The Java implementation implies this is a critical failure if the connection exists but fails.
