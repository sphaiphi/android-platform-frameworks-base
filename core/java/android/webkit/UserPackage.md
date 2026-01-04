# UserPackage - Reverse Engineering Documentation

## Executive Summary
`UserPackage` is a utility class to store a `UserHandle` and its corresponding `PackageInfo`. It is used to manage WebView provider packages across different Android users (profiles).

## Detailed Functionality
*   **`getPackageInfosAllUsers`**: Retrieves `PackageInfo` for a specific package across all users on the device.
*   **State Checks**: `isEnabledPackage()`, `isInstalledPackage()`.

## Java-to-C++ Translation Guide
*   **System Integration**: This interacts with `UserManager` and `PackageManager`, which are Android system services. In C++, this would involve Binder calls to system services.
