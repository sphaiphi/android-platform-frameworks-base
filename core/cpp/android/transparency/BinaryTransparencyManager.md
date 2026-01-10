# BinaryTransparencyManager - Reverse Engineering Documentation

## Executive Summary
`BinaryTransparencyManager` provides an interface to access information about binary artifacts installed on the device, such as signed images, APEX packages, and preloaded apps. It acts as a client-side wrapper for the `IBinaryTransparencyService` running in the system server.

## Architecture Overview
*   **System Service**: Registered as `Context.BINARY_TRANSPARENCY_SERVICE`.
*   **IPC**: Communicates with `IBinaryTransparencyService` (AIDL interface) via `mService`.
*   **Context**: Holds a reference to the Android `Context`.

## Data Model
*   **`mContext`**: Application context.
*   **`mService`**: Proxy to the remote `IBinaryTransparencyService`.

## API Reference
*   **`getSignedImageInfo()`**: Returns the VBMeta digest (String) describing signed images/partitions.
*   **`collectAllApexInfo(boolean includeTestOnly)`**: Returns a list of `ApexInfo` objects describing installed APEX modules.
*   **`collectAllUpdatedPreloadInfo(Bundle packagesToSkip)`**: Returns a list of `AppInfo` objects describing updated preloaded apps.
*   **`collectAllSilentInstalledMbaInfo(Bundle packagesToSkip)`**: Returns a list of `AppInfo` objects describing silently installed Mobile Broadband Association (MBA) apps.

## Java-to-C++ Translation Guide
*   **Binder Client**: This is a standard Android system service client. In C++, use `android::binder::Status` and the generated AIDL C++ backend (`IBinaryTransparencyService.h`) to communicate with the service.
*   **Service Retrieval**: Use `defaultServiceManager()->getService(String16("transparency"))` (check the exact service name in `Context.java` or `SystemServer.java`).
