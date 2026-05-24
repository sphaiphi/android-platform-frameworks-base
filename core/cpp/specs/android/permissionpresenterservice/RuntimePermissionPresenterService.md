# RuntimePermissionPresenterService - Reverse Engineering Documentation

## Executive Summary
`RuntimePermissionPresenterService` is a deprecated system service designed to provide information about how runtime permissions should be presented in the user interface. It allows the system to query an application's runtime permissions and receive a list of display-friendly information objects.

**Note**: This class is deprecated. Developers are encouraged to use `android.permission.PermissionControllerService` instead.

## Architecture Overview
- **Pattern**: Service-based Provider.
- **IPC**: Uses `IRuntimePermissionPresenter` AIDL interface for communication.
- **Asynchrony**: Uses `Handler` to execute queries on the main thread and `RemoteCallback` to return results to the caller asynchronously.
- **Lifecycle**: Standard Android `Service` lifecycle.

## Detailed Functionality

### Permission Querying
The service provides a single primary function: retrieving the runtime permissions for a specific package.
1.  **Request**: A client calls `getAppPermissions(packageName, callback)` via the binder.
2.  **Dispatch**: The binder stub wraps the request into a message and sends it to the service's `Handler` (running on the main looper).
3.  **Execution**: The `getAppPermissions` helper method calls the abstract `onGetAppPermissions(packageName)` method.
4.  **Response**: The resulting list of `RuntimePermissionPresentationInfo` is bundled and sent back via the provided `RemoteCallback`.

## Data Model
-   **Result Key**: `android.content.pm.permission.RuntimePermissionPresenter.key.result` - used in the result `Bundle`.
-   **Output Type**: `List<RuntimePermissionPresentationInfo>`.

## API Reference

### Abstract Methods
-   `onGetAppPermissions(@NonNull String packageName)`: Must be implemented by subclasses to return the list of permissions for the given package.

### Binder Interface
-   `IRuntimePermissionPresenter.Stub`: Handles the `getAppPermissions` IPC call.

## Java-to-C++ Translation Guide

### Service Implementation
If a C++ component needs to implement this interface:
1.  **Binder Stub**: Inherit from `BnRuntimePermissionPresenter` (generated from AIDL).
2.  **Threading**: Use a `Looper` or `Handler` equivalent to ensure thread safety or to offload work from the binder thread pool if necessary.
3.  **Callbacks**: Use `android::os::RemoteCallback` to send the result `Bundle`.

### Constants Mapping
Ensure the `SERVICE_INTERFACE` and `KEY_RESULT` strings match exactly.

## Implementation Risks
-   **Deprecation**: Since this service is deprecated, its usage in the system might be limited to legacy components. New features should target `PermissionControllerService`.
-   **Main Thread Blocking**: The implementation of `onGetAppPermissions` runs on the main looper. Long-running logic here will hang the service's UI thread.
