# PackageInstallObserver - Reverse Engineering Documentation

## Executive Summary
`PackageInstallObserver` is an internal helper class used to monitor the progress and outcome of package installation operations. It wraps the `IPackageInstallObserver2` AIDL interface, providing hooks for system components to receive notifications about installation success, failure, or the need for user intervention.

## Architecture Overview
- **Core Components**:
    - `mBinder`: An internal implementation of `IPackageInstallObserver2.Stub`.
- **Inheritance**: Contains a Binder stub for IPC with the `PackageManagerService`.

## Detailed Functionality

### IPackageInstallObserver2.Stub Implementation
**Purpose**: Receives callbacks from the install session.
**Mechanism**:
- `onUserActionRequired(Intent intent)`: Triggered when the installer needs the user to confirm permissions or other installation steps.
- `onPackageInstalled(String basePackageName, int returnCode, String msg, Bundle extras)`: Triggered when the installation process is complete. Provides the package name, basic outcome code, descriptive message, and a `Bundle` containing detailed failure information (e.g., `EXTRA_FAILURE_...`).

## API Reference
- `public IPackageInstallObserver2 getBinder()`: Returns the proxy object for IPC.
- `public void onUserActionRequired(Intent intent)`: Hook for subclasses to handle confirmation intents.
- `public void onPackageInstalled(String basePackageName, int returnCode, String msg, Bundle extras)`: Hook for subclasses to handle the final installation result.

## Java-to-C++ Translation Guide
- **Binder Stub**: Implement a C++ class inheriting from `android::content::pm::BnPackageInstallObserver2`.
- **Outcome Mapping**: Use standard integer constants for `returnCode` matching the native `PackageManager` definitions.
- **Bundle Handling**: Map the `extras` bundle to `android::os::Bundle` in C++.

## Implementation Risks
- **Result Interpretation**: The `returnCode` values are specific to the `PackageManager` and must be interpreted consistently with system definitions.
- **IPC Stability**: Ensure the observer remains alive for the duration of the installation session.
